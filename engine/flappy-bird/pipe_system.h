#pragma once
#include "transform.h"
#include "renderer.h"
#include "shader_program.h"
#include "texture.h"
#include "camera.h"
#include "game_clock.h"
#include "pipe.h"
#include "transform.h"

#include <vector>
#include <GLFW/glfw3.h>
#include <random>
#include "game_state.h"


struct PipeSystemData
{
	float speed;
	float interval;
	float repeats;
	float randomRange;
	float gap;

	PipeSystemData(float speed, float interval, float repeats, float randomRange, float gap)
	{
		this->speed = speed;
		this->interval = interval;
		this->repeats = repeats;
		this->randomRange = randomRange;
		this->gap = gap;
	}
};


class PipeSystem
{
public:
	PipeSystem(PipeSystemData psData, ShaderProgram& shaderProgram, Renderer& renderer, GameClock *clock, GLFWwindow* window);
	~PipeSystem();
	void Update(Camera* camera, GameState* game_state);
	std::vector<Pipe*> pipes;
	GameClock* clock;
	GLFWwindow* window;
	void Swap();
	void ResetPipeSystem();

	float speed;

	unsigned int GetNextPipeIndex();
	float gap;
	float halfScale;

private:

	int first;
	float middle;
	int last;
	float startDst;
	float interval;
	float repeats;
	float randomRange;

	float GetMiddlePoint();
	float RandomHeight();


	bool afterInit;
};

