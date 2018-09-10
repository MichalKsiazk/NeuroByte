#pragma once
#include "display.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <iostream>
#include <string>

#include "points_renderer.h"
#include "renderer.h"
#include "display.h"
#include "shader_builder.h"
#include "shader_program.h"
#include <vector>
#include "texture.h"
#include "render_models.h"
#include "transform.h"
#include "bird.h"
#include "camera.h"
#include "game_clock.h"
#include "pipe.h"
#include "pipe_system.h"
#include "game_state.h"
#include "population.h"

class GameDisplay : public Display
{
public:
	GameDisplay(unsigned int WIDTH, unsigned int HEIGHT, const char* name);
	~GameDisplay();
	void Start();
	void Update();


	GameState game_state;

	unsigned int WINDOW_WIDTH;
	unsigned int WINDOW_HEIGHT;

	Entity* background;

	Camera* camera;

	Transform* transform;


	GameClock* game_clock;
	PipeSystem* pipe_system;
	Population* population;


	unsigned int horizontalDifference;

};

inline void GameDisplay::Start()
{

	game_state = GameState::PRE_INIT;

	Texture background_t("res/sprites/background-day.png");
	game_clock = new GameClock();

	Renderer renderer(RM::Box2D());
	ShaderProgram shader = ShaderBuilder::NewShaderProgram("vs.vert", "fs.frag");

	PipeSystemData data(0.5f, 1.35f, 5, 0.3f, 0.6f);

	pipe_system = new PipeSystem(data, shader, renderer, game_clock, window);

	camera = new Camera (glm::vec3(0.0f, 0.0f, 0.0f), 70.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.0f, 100.0f, Camera::CameraType::CAMERA_2D);

	background = new Entity(new Transform(glm::vec3(0, 0.3f, 0.0f), glm::vec3(background_t.TextureRatio(1.5f), 0), glm::vec3(0, 0, 0)),
										shader,
										renderer,
										background_t);


	game_state = GameState::READY_TO_START;


	population = new Population(50, window, game_clock, &game_state, pipe_system);

}

inline void GameDisplay::Update()
{
	if (game_state == GameState::READY_TO_START)
	{
		game_state = GameState::RUNNING;
	}
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GL_TRUE)
	{
		game_state = GameState::RESTART_PLS;
	}

	if (game_state == GameState::RESTART_PLS)
	{
		pipe_system->ResetPipeSystem();
		population->ResetPopulation();
		game_state = GameState::READY_TO_START;
	}

	game_clock->CalculateDeltaTime();
	glfwMakeContextCurrent(window);
	glClear(GL_COLOR_BUFFER_BIT);
	


	background->Update(camera);
	pipe_system->Update(camera, &game_state);
	population->Update(camera);
	horizontalDifference = pipe_system->GetNextPipeIndex();
	glfwSwapBuffers(window);
	glfwPollEvents();
}

