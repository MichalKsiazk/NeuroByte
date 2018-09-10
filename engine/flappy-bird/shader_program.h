#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include <glm/glm.hpp>

class ShaderProgram
{
public:

	unsigned int programID;

	unsigned int vertex_shader;
	unsigned int geometry_shader;
	unsigned int fragment_shader;

	void UseProgram();
	ShaderProgram(unsigned int programID, unsigned int vertex_shader, unsigned int geometry_shader, unsigned int fragment_shader);
	ShaderProgram()
	{
		programID = 0;
		vertex_shader = 0;
		geometry_shader = 0;
		fragment_shader = 0;
	}
	~ShaderProgram();


	void SetFloat(const std::string &uniform_name, float value_to_set);
	void SetVec3(const std::string &uniform_name, glm::vec3 value_to_set);
	void SetMat4(const std::string &uniform_name, glm::mat4 mat4);

};

inline ShaderProgram::ShaderProgram(unsigned int programID, unsigned int vertex_shader, unsigned int geometry_shader, unsigned int fragment_shader)
{
	this -> programID = programID;
	this -> vertex_shader = vertex_shader;
	this -> geometry_shader = geometry_shader;
	this -> fragment_shader = fragment_shader;
}




