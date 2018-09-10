#include "stdafx.h"
#include "entity.h"




Entity::Entity(Transform* transform, ShaderProgram& shaderProgram, Renderer& renderer, Texture& texture)
{
	this->transform = transform;
	this->shaderProgram = shaderProgram;
	this->renderer = renderer;
	this->texture = texture;
}

Entity::Entity()
{
}

void Entity::Update(Camera* camera)
{
	shaderProgram.UseProgram();
	shaderProgram.SetMat4("modelMatrix", transform->GetModel());
	shaderProgram.SetMat4("cameraMatrix", camera->GetViewProjection2D());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.textureID);

	glBindAttribLocation(shaderProgram.programID, 0, "in_position");
	glBindAttribLocation(shaderProgram.programID, 1, "in_coords");
	glUniform1i(glGetUniformLocation(shaderProgram.programID, "txtx"), 0);
	renderer.RenderIndexed();
}


Entity::~Entity()
{
}
