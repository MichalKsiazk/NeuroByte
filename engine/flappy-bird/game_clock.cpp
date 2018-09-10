#include "stdafx.h"
#include "game_clock.h"


void GameClock::CalculateDeltaTime()
{
	oldTime = currentTime;
	currentTime = glfwGetTime();
	
	deltaTime = currentTime - oldTime;

	//std::cout << deltaTime << std::endl;
}


double GameClock::GetDeltaTime()
{
	return deltaTime;
}

double GameClock::GetCurrentTime()
{
	return currentTime;
}

GameClock::GameClock()
{
	oldTime = glfwGetTime();
	currentTime = glfwGetTime();
}


GameClock::~GameClock()
{
}
