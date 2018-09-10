#pragma once

#include <glm/vec3.hpp>

class PointsRenderer
{

	

public:
	PointsRenderer(glm::vec3 points[], unsigned int element_bytes, unsigned int lenght);
	unsigned int VBO;
	unsigned int lenght;

	void RenderPoints();

	virtual ~PointsRenderer();
};

