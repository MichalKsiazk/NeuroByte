#include "stdafx.h"
#include "shader_builder.h"




ShaderProgram ShaderBuilder::NewShaderProgram(std::string vs_filepath, std::string gs_filepath, std::string fs_filepath)
{
	unsigned int program = glCreateProgram();

	unsigned int vs = NewShaderFromFile(GL_VERTEX_SHADER, vs_filepath);
	unsigned int gs = NewShaderFromFile(GL_GEOMETRY_SHADER, gs_filepath);
	unsigned int fs = NewShaderFromFile(GL_FRAGMENT_SHADER, fs_filepath);


	glAttachShader(program, vs);
	glAttachShader(program, gs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	int link_status;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);

	DebugProgram(link_status, program, vs_filepath, gs_filepath, fs_filepath);

	glDeleteShader(vs);
	glDeleteShader(gs);
	glDeleteShader(fs);

	return ShaderProgram(program, vs, gs, fs);
}

ShaderProgram ShaderBuilder::NewShaderProgram(std::string vs_filepath, std::string fs_filepath)
{
	unsigned int program = glCreateProgram();

	unsigned int vs = NewShaderFromFile(GL_VERTEX_SHADER, vs_filepath);
	unsigned int fs = NewShaderFromFile(GL_FRAGMENT_SHADER, fs_filepath);


	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	int link_status;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);

	glDeleteShader(vs);
	glDeleteShader(fs);

	DebugProgram(link_status, program, vs_filepath, "NULL", fs_filepath);

	return ShaderProgram(program, vs, 0, fs);
}

ShaderProgram ShaderBuilder::NewShaderProgram(unsigned int vs, unsigned int gs, unsigned int fs)
{

	unsigned int program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, gs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	int link_status;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);

	if (link_status != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(program, 1024, &log_length, message);
		std::cout << "SHADER PROGRAM LINK ERROR! : " << message << std::endl;
	}

	return ShaderProgram(program, vs, gs, fs);
}

unsigned int ShaderBuilder::NewShaderFromSource(GLenum shader_type, std::string source)
{
	

	return 0;
}


unsigned int ShaderBuilder::NewShaderFromFile(GLenum shader_type, std::string filename)
{

	unsigned int shader = glCreateShader(shader_type);

	std::string raw_source = ReadFile(filename);

	const char* source = raw_source.c_str();

	//std::cout << source << std::endl;

	glShaderSource(shader, 1, &source, NULL);

	glCompileShader(shader);

	int compile_status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

	DebugShader(compile_status, shader, filename);

	return shader;
}

std::string ShaderBuilder::ReadFile(std::string filename)
{

	std::string source = "";
	
	std::string line;

	std::ifstream shader_file(filename);
	if (shader_file.is_open())
	{
		while (getline(shader_file, line))
		{
			source += line;
			source += "\n";
		}
		shader_file.close();
	}


	return source;
}

void ShaderBuilder::DebugShader(int &compile_status, unsigned int &shader, std::string &source)
{
	if (compile_status != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(shader, 1024, &log_length, message);
		std::cout << "SHADER COMPILATION ERROR! : " << message << std::endl;
	}
	else
	{
		std::cout << "SHADER COMPILED! : " << source << std::endl;
	}
}

void ShaderBuilder::DebugProgram(int &link_status, unsigned int &program, std::string &vs, std::string gs, std::string &fs)
{
	if (link_status != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(program, 1024, &log_length, message);
		std::cout << "SHADER PROGRAM LINK ERROR! : " << message << std::endl;
	}
	else
	{
		std::cout << "PROGRAM LINKED! : " << vs << " | " << gs << " | " << fs << std::endl;
	}
}

