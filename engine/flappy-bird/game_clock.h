#pragma once

#include <time.h>
#include <GLFW/glfw3.h>
#include <iostream>

class GameClock
{
public:



	void CalculateDeltaTime();

	double GetDeltaTime();
	double GetCurrentTime();

	GameClock();
	~GameClock();
private:
	double deltaTime;
	double oldTime;
	double currentTime;
};

