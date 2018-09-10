#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>




struct Camera
{


	static enum CameraType
	{
		CAMERA_3D,
		CAMERA_2D
	};


public:


	CameraType type;

	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar, CameraType type)
	{
		this->type = type;
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 GetViewProjection3D() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	inline glm::mat4 GetViewProjection2D() const
	{
		glm::mat4 position_matrix = glm::translate(-pos);
		return position_matrix;
	}



	void MoveForward(float amt)
	{
		pos += forward * amt;
	}

	void MoveRight(float amt)
	{
		pos += glm::cross(up, forward) * amt;
	}

	void Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	void RotateY(float angle)
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, UP);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};