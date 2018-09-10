#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "shader_builder.h"
#include "bird.h"
#include "pipe_system.h"
#include "game_clock.h"
#include "camera.h"
#include "game_state.h"
#include "pipe.h"
#include "brain.h"

class Population
{
public:

	std::vector<Bird> birds;

	unsigned int size;

	PipeSystem* pipe_system;
	GLFWwindow* window;
	GameClock* game_clock;
	GameState* game_state;
	Population(unsigned int size, GLFWwindow* window, GameClock* game_clock, GameState* game_state, PipeSystem* pipe_system);
	
	void Update(Camera* camera);
	void Collide();
	~Population();

	float horizontalDst;
	float nextPipeHeight;

	float maxFitness;
	int maxIndex;

	glm::vec3 RandomColor();
	float RandomFloat(float min, float max);
	void ResetPopulation();
	std::vector<int> SortBest();
	Brain* Mutate_1(Brain* b1, Brain* b2, int target);
	Brain* Mutate_2(Brain* b1, int target, float range);
	Brain* Mutate_3(Brain* b1, Brain* b2, int target);
	Brain* Copy_1(Brain* b1, int target);

	float Clamp01(float input);

};

