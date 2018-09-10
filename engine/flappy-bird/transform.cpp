#include "stdafx.h"
#include "transform.h"


Transform::Transform(const glm::vec3 position, const glm::vec3 scale, const glm::vec3 rotation)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Transform::~Transform()
{
}
