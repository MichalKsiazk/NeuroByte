#pragma once

#include <GL/glew.h>

#include "shader_program.h"
#include <string>
#include <fstream>
#include <iostream>

namespace ShaderBuilder
{
	ShaderProgram NewShaderProgram(std::string vs_filepath, std::string gs_filepath, std::string fs_filepath);
	ShaderProgram NewShaderProgram(std::string vs_filepath, std::string fs_filepath);

	ShaderProgram NewShaderProgram(unsigned int vs, unsigned int gs, unsigned int fs);

	unsigned int NewShaderFromSource(GLenum shader_type, std::string source);

	unsigned int NewShaderFromFile(GLenum shader_type, std::string filename);

	std::string ReadFile(std::string filename);

	void DebugShader(int &compile_status, unsigned int &shader, std::string &source);
	void DebugProgram(int &link_status, unsigned int &program, std::string &vs, std::string gs, std::string &fs);
}



