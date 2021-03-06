// flappy-bird.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <iostream>
#include <string>
#include <time.h>
#include "display.h"
#include "GameDisplay.h"



int main(void)
{
	
	//Display NEURAL_NETWORK_CONTEXT(600, 400, "DEBUGGER");
	GameDisplay GAME_CONTEXT(600, 600, "GAME");

	glewInit();


	GAME_CONTEXT.Start();

	while (!glfwWindowShouldClose(GAME_CONTEXT.window))
	{
		GAME_CONTEXT.Update();
	}
	glfwTerminate();

	return 0;
}


