#include "stdafx.h"
#include "pipe.h"


Pipe::Pipe(Transform * transform, ShaderProgram & shaderProgram, Renderer & renderer, Texture & texture, GameClock * clock)
{
	this->transform = transform;
	this->shaderProgram = shaderProgram;
	this->renderer = renderer;
	this->texture = texture;
	this->game_clock = clock;



	collider = new RectCollider2D(glm::vec2(transform->position.x, transform->position.y), glm::vec2(transform->scale.x, transform->scale.y));
}

void Pipe::Update(Camera* camera)
{
	Entity::Update(camera);
	collider->position = glm::vec2(transform->position.x, transform->position.y);
}

Pipe::~Pipe()
{
}
