#include "stdafx.h"
#include "pipe_system.h"

PipeSystem::PipeSystem(PipeSystemData psData, ShaderProgram& shaderProgram, Renderer& renderer, GameClock *clock, GLFWwindow* window)
{
	this->speed = psData.speed;
	this->interval = psData.interval;
	this->repeats = psData.repeats;
	this->randomRange = psData.randomRange;
	this->gap = psData.gap;

	this->clock = clock;
	this->window = window;
	afterInit = false;
	first = 0;
	last = repeats * 2 - 2;

	startDst = 2.5f;

	Texture texture("res/sprites/pipe-green.png");

	halfScale = glm::vec3(texture.TextureRatio(1.6f), 0).y * 0.5f;
	for (int i = 0; i < repeats; i++)
	{

		float randomHeight = RandomHeight();

		std::cout << "RANDOM: " << randomHeight << std::endl;

		pipes.push_back(new Pipe(new Transform(glm::vec3(startDst + interval * i, randomHeight - gap - halfScale * 0.5f, 0.0f), glm::vec3(texture.TextureRatio(1.6f), 0), glm::vec3(0, 0, 0)),
			shaderProgram,
			renderer,
			texture, clock));
		pipes.push_back(new Pipe(new Transform(glm::vec3(startDst + interval * i, randomHeight + gap + halfScale * 0.5f, 0.0f), glm::vec3(texture.TextureRatio(1.6f), 0), glm::vec3(0, 0, 180)),
			shaderProgram,
			renderer,
			texture, clock));
	}
	middle = GetMiddlePoint();
}


PipeSystem::~PipeSystem()
{
}

void PipeSystem::Update(Camera* camera, GameState* game_state)
{
	for(int i = 0; i < pipes.size(); i++)
	{ 
		pipes.at(i)->Update(camera);

		if (*game_state == GameState::RUNNING)
		{
			pipes.at(i)->transform->position.x -= speed * clock->GetDeltaTime();
		}
	}

	if (*game_state != GameState::RUNNING)
	{
		return;
	}

	if (std::abs(pipes.at(first)->transform->position.x) > middle && pipes.at(first)->transform->position.x < 0)
	{
		Swap();
	}
}

void PipeSystem::Swap()
{
	float randomHeight = RandomHeight();

	pipes.at(first)->transform->position.y = randomHeight - gap - halfScale * 0.5f;
	pipes.at(first + 1)->transform->position.y = randomHeight + gap + halfScale * 0.5f;

	pipes.at(first)->transform->position.x = pipes.at(last)->transform->position.x + interval;
	pipes.at(first + 1)->transform->position.x = pipes.at(last)->transform->position.x + interval;
	int newFirst = first == pipes.size() - 2 ? 0 : first + 2;
	last = first;
	first = newFirst;
	middle = GetMiddlePoint();
}


void PipeSystem::ResetPipeSystem()
{

	first = 0;
	last = repeats * 2 - 2;

	for (int i = 0; i < pipes.size(); i+=2)
	{

		float randomHeight = RandomHeight();


		pipes.at(i)->transform->position = glm::vec3(startDst + interval * ((float)i * 0.5f), randomHeight - gap - halfScale * 0.5f, 0.0f);
		pipes.at(i + 1)->transform->position = glm::vec3(startDst + interval * ((float)i * 0.5f), randomHeight + gap + halfScale * 0.5f, 0.0f);

	}
	middle = GetMiddlePoint();
}





float PipeSystem::GetMiddlePoint()
{
	return (pipes.at(first)->transform->position.x + pipes.at(last)->transform->position.x) * 0.5f;
}

float PipeSystem::RandomHeight()
{
	int rr = (int)(randomRange * 100);

	int range = rr - -rr + 1;

	float output = ((float)(rand() % range + -rr)) * 0.01f;
	return output;
}

unsigned int PipeSystem::GetNextPipeIndex()
{

	float min = 100.0f;

	unsigned int index = 100;

	for (int i = 0; i < pipes.size(); i += 2)
	{

		float x = pipes.at(i)->transform->position.x;

		if (x > 0 && x < min)
		{
			min = x;
			index = i;
		}
	}
	return index;
}