#pragma once


#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

#include "render_models.h"


class Renderer
{
public:

	Renderer(std::vector<glm::vec3> vertices, GLenum MODE);

	Renderer(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
	Renderer(RenderModel render_model);
	Renderer() {

	}

	unsigned int VBO[2];
	unsigned int VAO;


	unsigned int vertices_buffer;
	unsigned int indices_buffer;
	unsigned int texture_coords_buffer;


	unsigned int lenght;

	GLenum MODE;

	void Render();
	void RenderIndexed();

	~Renderer();

};


