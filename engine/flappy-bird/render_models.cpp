#include "stdafx.h"
#include "render_models.h"



RenderModel::~RenderModel()
{
}


RenderModel::RenderModel(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> texture_coords)
{
	this->vertices = vertices;
	this->indices = indices;
	this->texture_coords = texture_coords;
}

RenderModel RM::Box2D()
{
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> texture_coords;

	vertices.push_back(glm::vec3(-0.25f, -0.25f, 0));
	vertices.push_back(glm::vec3(0.25f, -0.25f, 0));
	vertices.push_back(glm::vec3(-0.25f, 0.25f, 0));
	vertices.push_back(glm::vec3(0.25f, 0.25f, 0));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(1);

	texture_coords.push_back(glm::vec2(0, 0));
	texture_coords.push_back(glm::vec2(1, 0));
	texture_coords.push_back(glm::vec2(0, 1));
	texture_coords.push_back(glm::vec2(1, 1));

	return RenderModel(vertices, indices, texture_coords);
}

