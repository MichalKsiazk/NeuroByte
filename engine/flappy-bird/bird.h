#pragma once
#include "entity.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "transform.h"
#include "renderer.h"
#include "shader_program.h"
#include "texture.h"
#include "camera.h"
#include "game_clock.h"
#include "collider_2d.h" 
#include "game_state.h"
#include "brain.h"

enum BirdState
{
	ALIVE,
	DEAD
};



class Bird : public Entity
{
public:
	Bird(Transform* transform, ShaderProgram& shaderProgram, Renderer& renderer, Texture& texture, GLFWwindow *window, GameClock *clock);

	BirdState bird_state;

	void Update(Camera* camera, GameState* game_state);

	float gravity;

	bool lastFrameMouseInput;
	float mg;
	float speed;
	float score;
	RectCollider2D *collider;

	Brain* brain;

	glm::vec3 customColor;


	GLFWwindow *window;
	~Bird();
protected:
	GameClock *game_clock;
};

