#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Display
{
public:
	GLFWwindow * window;

	Display();
	Display(int WIDTH, int HEIGHT, const char* name);
	virtual ~Display();

	


};

