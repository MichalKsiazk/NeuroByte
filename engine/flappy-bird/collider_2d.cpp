#include "stdafx.h"
#include "collider_2d.h"


RectCollider2D::RectCollider2D(glm::vec2 position, glm::vec2 dimensions)
{
	this->position = position;
	this->dimensions = dimensions;
}


RectCollider2D::~RectCollider2D()
{
}

bool RectCollider2D::Collide(RectCollider2D c)
{
	//std::cout << position.x << " " << position.y << std::endl;

	float verticalDst = std::sqrtf(std::powf(position.y - c.position.y, 2));
	float horizontalDst = std::sqrtf(std::powf(position.x - c.position.x, 2));


	bool vertical = dimensions.y * 0.5 + c.dimensions.y * 0.5 > verticalDst * 2;

	bool horizontal = dimensions.x * 0.5 + c.dimensions.x * 0.5 > horizontalDst * 2;

	//std::cout << c.dimensions.y << std::endl;

	if (vertical && horizontal)
	{
		//std::cout << "sdfdsf" << std::endl;
		return true;
	}
	return false;
}

CircleCollider2D::CircleCollider2D(glm::vec2 position, float radius)
{
	this->position = position;
	this->radius = radius;
}

CircleCollider2D::~CircleCollider2D()
{

}

bool CircleCollider2D::Collide(CircleCollider2D c)
{
	float triggerDistance = this->radius + c.radius;

	float distance = std::sqrt(std::pow(position.x - c.position.x, 2) + std::pow(position.y - c.position.y, 2));

	if (distance < triggerDistance)
	{
		return true;
	}

	return false;
}
