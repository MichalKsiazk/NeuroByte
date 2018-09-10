#include "stdafx.h"
#include "shader_program.h"


void ShaderProgram::UseProgram()
{
	glUseProgram(programID);
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::SetFloat(const std::string &uniform_name, float value_to_set)
{
	glUniform1f(glGetUniformLocation(programID, uniform_name.c_str()), value_to_set);
}

void ShaderProgram::SetVec3(const std::string &uniform_name, glm::vec3 value_to_set)
{
	glUniform3f(glGetUniformLocation(programID, uniform_name.c_str()), value_to_set.x, value_to_set.y, value_to_set.z);
}

void ShaderProgram::SetMat4(const std::string & uniform_name, glm::mat4 mat4)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, uniform_name.c_str()),1, GL_FALSE, glm::value_ptr(mat4));
}
