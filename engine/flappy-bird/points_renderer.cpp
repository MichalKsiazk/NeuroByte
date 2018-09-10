#include "stdafx.h"
#include "points_renderer.h"

#include <GL/glew.h>
#include <iostream>

void PointsRenderer::RenderPoints()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,(void*) 0);
	glDrawArrays(GL_POINTS, 0, lenght);
	glDisableVertexAttribArray(0);
}


PointsRenderer::PointsRenderer(glm::vec3 points[], unsigned int element_bytes, unsigned int lenght)
{
	std::cout << lenght << std::endl;

	this->lenght = lenght;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, element_bytes, &points[0], GL_STATIC_DRAW);


}


PointsRenderer::~PointsRenderer()
{
}
