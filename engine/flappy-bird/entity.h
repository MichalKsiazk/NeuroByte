#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "transform.h"
#include "renderer.h"
#include "shader_program.h"
#include "texture.h"
#include "camera.h"
class Entity
{
public:
	Entity* parent;
	Transform* transform;
	ShaderProgram shaderProgram;
	Renderer renderer;
	Texture texture;

	Entity(Transform* transform, ShaderProgram& shaderProgram, Renderer& renderer, Texture& texture);

	Entity();

	virtual void Update(Camera* camera);


	~Entity();
protected:

};

