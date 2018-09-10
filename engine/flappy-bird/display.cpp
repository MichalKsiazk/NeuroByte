#include "stdafx.h"
#include "display.h"


Display::Display()
{
}

Display::Display(int WIDTH, int HEIGHT, const char* name)
{
	if (!glfwInit())
		return;


	window = glfwCreateWindow(WIDTH, HEIGHT, name, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}


	glfwMakeContextCurrent(window);

}


Display::~Display()
{
}
