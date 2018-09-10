#include "stdafx.h"
#include "bird.h"



Bird::Bird(Transform* transform, ShaderProgram& shaderProgram, Renderer& renderer, Texture& texture, GLFWwindow *window, GameClock *clock)
{
	this->transform = transform;
	this->shaderProgram = shaderProgram;
	this->renderer = renderer;
	this->texture = texture;
	this->window = window;
	this->game_clock = clock;
	this->bird_state = BirdState::ALIVE;
	gravity = 2.2f; 
	mg = gravity;
	score = 0;

	collider = new RectCollider2D(glm::vec2(transform->position.x, transform->position.y), glm::vec2(transform->scale.x, transform->scale.y));
}

void Bird::Update(Camera* camera, GameState* game_state)
{

	shaderProgram.UseProgram();
	shaderProgram.SetVec3("customColor", customColor);
	Entity::Update(camera);


	collider->position = glm::vec2(transform->position.x, transform->position.y);

	bool currentFrameInput = false;

	bool jump = brain->Update(&score);

	if ((jump || glfwGetKey(window, GLFW_KEY_SPACE) == GL_TRUE) && !lastFrameMouseInput) 
	{
		currentFrameInput = true;
	}
	else
	{
		currentFrameInput = false;
	}

	switch (*game_state)
	{
		case GameState::RUNNING:
			switch (bird_state)
			{
				case ALIVE:
					score += speed * game_clock->GetDeltaTime();
					if (gravity < mg)
					{
						transform->rotation.z = 20;
						transform->position.y -= gravity * game_clock->GetDeltaTime();
						gravity += 8.0f * game_clock->GetDeltaTime();
					}
					else
					{
						transform->position.y -= gravity * game_clock->GetDeltaTime();
						if (transform->rotation.z > -90)
						{
							transform->rotation.z -= 0.2f;
						}
					}
					if (transform->position.y > 1 || transform->position.y < -1)
					{
						bird_state = BirdState::DEAD;
					}
					break;
				case DEAD:
					transform->position.x -= speed * game_clock->GetDeltaTime();
					break;
			}
			break;
		case GameState::READY_TO_START:
			transform->position.y = std::sin(game_clock->GetCurrentTime() * 5) * 0.05f;
			transform->position.x = 0;
			transform->rotation.z = 0;
			bird_state = BirdState::ALIVE;
			score = 0;
			break;
	}
	if (currentFrameInput)
	{
		gravity = -mg;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GL_TRUE) 
	{
		lastFrameMouseInput = true;
	}
	else
	{
		lastFrameMouseInput = false;
	}
	
}


Bird::~Bird()
{
}
