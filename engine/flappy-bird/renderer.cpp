#include "stdafx.h"
#include "renderer.h"

#include <iostream>

Renderer::Renderer(std::vector<glm::vec3> vertices, GLenum MODE)
{
	this->MODE = MODE;
	this->lenght = vertices.size();

	std::cout << lenght << std::endl;

	unsigned int size_in_bytes = vertices.size() * sizeof(vertices.at(0));

	std::cout << size_in_bytes << std::endl;

	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, size_in_bytes, &vertices[0], GL_STATIC_DRAW);
}


Renderer::Renderer(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices)
{
	this->MODE = GL_TRIANGLES;

	this->lenght = indices.size();
	unsigned int size_in_bytes = vertices.size() * sizeof(vertices.at(0));

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, size_in_bytes, &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &VBO[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);  
	glBindVertexArray(0); 
}

Renderer::Renderer(RenderModel render_model)
{
	this->MODE = GL_TRIANGLES;
	this->lenght = render_model.indices.size();

	unsigned int size_in_bytes = render_model.vertices.size() * sizeof(render_model.vertices.at(0));


	glGenBuffers(1, &vertices_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
	glBufferData(GL_ARRAY_BUFFER, size_in_bytes, &render_model.vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	size_in_bytes = render_model.indices.size() * sizeof(unsigned int);

	glGenBuffers(1, &indices_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_in_bytes, &render_model.indices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);

	size_in_bytes = render_model.texture_coords.size() * sizeof(render_model.texture_coords.at(0));

	glGenBuffers(1, &texture_coords_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, texture_coords_buffer);
	glBufferData(GL_ARRAY_BUFFER, size_in_bytes, &render_model.texture_coords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	
}

void Renderer::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
	glDrawArrays(MODE, 0, lenght);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Renderer::RenderIndexed()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	//glBindBuffer(GL_ARRAY_BUFFER, texture_coords_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
	glDrawElements(GL_TRIANGLES, lenght, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindVertexArray(0);
}



Renderer::~Renderer()
{
}

