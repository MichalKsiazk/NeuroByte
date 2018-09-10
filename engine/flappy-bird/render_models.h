#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

class RenderModel
{
public:
	RenderModel(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> texture_coords);
	~RenderModel();

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> texture_coords;


};

namespace RM
{
	RenderModel Box2D();
}

