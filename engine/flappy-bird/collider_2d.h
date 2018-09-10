#pragma once
#include "transform.h"
#include <glm/vec2.hpp>
#include <math.h>
#include <iostream>

class RectCollider2D
{
public:
	glm::vec2 position;
	glm::vec2 dimensions;

	RectCollider2D(glm::vec2 position, glm::vec2 dimensions);
	~RectCollider2D();

	bool Collide(RectCollider2D c);
};

class CircleCollider2D
{
public:
	glm::vec2 position;
	float radius;

	CircleCollider2D(glm::vec2 position, float radius);
	~CircleCollider2D();

	bool Collide(CircleCollider2D c);
};