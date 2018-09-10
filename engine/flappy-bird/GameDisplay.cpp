#include "stdafx.h"
#include "GameDisplay.h"


GameDisplay::GameDisplay(unsigned int WIDTH, unsigned int HEIGHT, const char* name)
{
	if (!glfwInit())
		return;


	window = glfwCreateWindow(WIDTH, HEIGHT, name, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	WINDOW_WIDTH = WIDTH;
	WINDOW_HEIGHT = HEIGHT;


	glfwMakeContextCurrent(window);

}


GameDisplay::~GameDisplay()
{
}
