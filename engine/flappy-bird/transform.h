#pragma once

#define GLM_ENABLE_EXPERIMENTAL




#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <math.h>


class Transform
{
public:
	Transform(const glm::vec3 position, const glm::vec3 scale, const glm::vec3 rotation);

	Transform()
	{
		this->position = glm::vec3();
		this->rotation = glm::vec3();
		this->scale = glm::vec3();
	}

	~Transform();

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::mat4 GetModel()
	{

		glm::mat4 position_matrix = glm::translate(position);
		glm::mat4 scale_matrix = glm::scale(scale);
		glm::mat4 rot_x = glm::rotate(D2R(rotation.x), glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rot_y = glm::rotate(D2R(rotation.y), glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rot_z = glm::rotate(D2R(rotation.z), glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotation_matrix = rot_x * rot_y * rot_z;

		return position_matrix * rotation_matrix * scale_matrix;
	}

	float D2R(float d)
	{
		return (std::atan(1) * 4) * d / 180.0f;
	}

};

