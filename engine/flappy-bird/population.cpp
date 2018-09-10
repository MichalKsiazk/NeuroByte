#include "stdafx.h"
#include "population.h"


Population::Population(unsigned int size, GLFWwindow* window, GameClock* game_clock, GameState* game_state, PipeSystem* pipe_system)
{

	this->size = size;
	this->window = window;
	this->game_clock = game_clock;
	this->game_state = game_state;
	this->pipe_system = pipe_system;

	maxFitness = 0;
	maxIndex = -1;

	Texture bird_t("res/sprites/yellowbird-midflap.png");
	ShaderProgram shader = ShaderBuilder::NewShaderProgram("color_v3.vert", "color_v3.frag");
	Renderer renderer(RM::Box2D());

	for (int i = 0; i < size; i++)
	{

		birds.push_back(Bird(new Transform(glm::vec3(0, 0.0f, 0.0f), glm::vec3(bird_t.TextureRatio(1.2f), 0), glm::vec3(0, 0, 0)),
			shader,
			renderer,
			bird_t, window, game_clock));

		birds.at(i).speed = pipe_system->speed;
		birds.at(i).brain = new Brain(birds.at(i).transform, &horizontalDst, &nextPipeHeight);

		birds.at(i).customColor = RandomColor();
	}
}


void Population::Update(Camera* camera)
{

	int deads = 0;

	int nextPipeIndex = pipe_system->GetNextPipeIndex();

	horizontalDst = pipe_system->pipes.at(nextPipeIndex)->transform->position.x;

	nextPipeHeight = pipe_system->pipes.at(nextPipeIndex)->transform->position.y + pipe_system->halfScale * 0.5f + pipe_system->gap ;

	//std::cout << birds.at(0).brain->VerticalDst() << std::endl;

	for (int i = 0; i < birds.size(); i++)
	{

		birds.at(i).Update(camera, game_state);

		if (birds.at(i).brain->fitness > maxFitness)
		{
			maxFitness = birds.at(i).brain->fitness;
			maxIndex = i;
			std::cout << "MAX: " << maxIndex << "  " << maxFitness << std::endl;
		}

		if (birds.at(i).bird_state == BirdState::DEAD)
		{
			deads++;
		}
	}
	if (deads == birds.size())
	{
		std::vector<int> rank = SortBest();

		int index = size;

		for (int i = 0; i < 10; i++)
		{
			index--;

			birds.at(rank.at(index)).brain = new Brain(birds.at(rank.at(index)).transform, &horizontalDst, &nextPipeHeight);
		}
		for (int i = 0; i < 10; i++)
		{
			index--;
			birds.at(rank.at(index)).brain = Mutate_2(birds.at(0).brain, rank.at(index), 0.01f);
		}
		if (birds.at(rank.at(0)).brain->fitness > 4.0f && birds.at(rank.at(1)).brain->fitness > 4.0f)
		{
			for (int i = 0; i < 5; i++)
			{
				index--;
				birds.at(rank.at(index)).brain = Mutate_3(birds.at(0).brain, birds.at(rank.at(1)).brain, rank.at(index));
			}
		}
		*game_state = GameState::RESTART_PLS;
	}
	Collide();
} 

void Population::Collide()
{

	for (int b = 0; b < birds.size(); b++)
	{
		for (int p = 0; p < pipe_system->pipes.size(); p++)
		{
			bool c = birds.at(b).collider->Collide(*pipe_system->pipes.at(p)->collider);
			if (c)
			{
				birds.at(b).bird_state = BirdState::DEAD;
			}
		}
	}
}

Population::~Population()
{
}

glm::vec3 Population::RandomColor()
{
	return glm::vec3(RandomFloat(0.1f, 1.0f), RandomFloat(0.1f, 1.0f), RandomFloat(0.1f, 1.0f));
}

float Population::RandomFloat(float min, float max) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

void Population::ResetPopulation()
{
	for (int i = 0; i < size; i++)
	{
		birds.at(i).brain = new Brain(birds.at(i).transform, &horizontalDst, &nextPipeHeight);
	}
}

std::vector<int> Population::SortBest()
{
	std::vector<int> output;
	float f = -100;
	int bestIndex = -1;

	std::vector<bool> checkedIndexes;
	for (int i = 0; i < size; i++)
	{
		checkedIndexes.push_back(false);
	}


	for (int x = 0; x < size; x++)
	{
		for (int i = 0; i < size; i++)
		{
			if (birds.at(i).brain->fitness > f && !checkedIndexes.at(i))
			{
				bestIndex = i;
				f = birds.at(i).brain->fitness;
				//std::cout << "!" << std::endl;
			}
		}
		f = -100;
		output.push_back(bestIndex);
		checkedIndexes.at(bestIndex) = true;
	}
	//for (int i = 0; i < size; i++)
	//{
		//std::cout << output.at(i) << ": " << birds.at(output.at(i)).brain->fitness << std::endl;
	//}

	return output;
}

Brain* Population::Mutate_1(Brain* b1, Brain* b2, int target)
{
	Brain* output = new Brain(birds.at(target).transform, &horizontalDst, &nextPipeHeight);

	float randomInputBias = RandomFloat(0, 1.0f);
	if (randomInputBias > 0.5f)
	{
		output->input_bias = b1->input_bias;
	}
	else
	{
		output->input_bias = b2->input_bias;
	}
	float randomHiddenBias = RandomFloat(0, 1.0f);
	if (randomHiddenBias > 0.5f)
	{
		output->hidden_bias = b1->hidden_bias;
	}
	else
	{
		output->input_bias = b2->hidden_bias;
	}
	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < 4; x++)
		{
			float random = RandomFloat(0, 1.0f);
			if (random > 0.5f)
			{
				output->input_layer[i][x] = b1->input_layer[i][x];
			}
			else
			{
				output->input_layer[i][x] = b2->input_layer[i][x];
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		float random = RandomFloat(0, 1.0f);
		if (random > 0.5f)
		{
			output->hidden_layer[i] = b1->hidden_layer[i];
		}
		else
		{
			output->hidden_layer[i] = b2->hidden_layer[i];
		}
	}
	return output;
}

Brain * Population::Mutate_2(Brain * b1, int target, float range)
{
	Brain* output = new Brain(birds.at(target).transform, &horizontalDst, &nextPipeHeight);
	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < 4; x++)
		{
			output->input_layer[i][x] = Clamp01(b1->input_layer[i][x] += RandomFloat(-range, range));

		}
	}
	for (int i = 0; i < 4; i++)
	{
		output->hidden_layer[i] = Clamp01(b1->hidden_layer[i] += RandomFloat(-range, range));
	}
	output->hidden_bias = Clamp01(b1->hidden_bias += RandomFloat(-range, range));
	output->input_bias = Clamp01(b1->input_bias += RandomFloat(-range, range));
	return output;
}

Brain * Population::Mutate_3(Brain * b1, Brain * b2, int target)
{
	Brain* output = new Brain(birds.at(target).transform, &horizontalDst, &nextPipeHeight);

	output->input_bias = (b1->input_bias + b2->input_bias) / 2;
	output->hidden_bias = (b1->hidden_bias + b2->hidden_bias) / 2;

	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < 4; x++)
		{
			output->input_layer[i][x] = (b1->input_layer[i][x] + b2->input_layer[i][x]) / 2;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		output->hidden_layer[i] = (b1->hidden_layer[i] + b2->hidden_layer[i]) / 2;
	}


	return output;
}

Brain * Population::Copy_1(Brain * b1, int target)
{
	Brain* output = new Brain(birds.at(target).transform, &horizontalDst, &nextPipeHeight);
	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < 4; x++)
		{
				output->input_layer[i][x] = b1->input_layer[i][x];
		}
	}
	for (int i = 0; i < 4; i++)
	{
		output->hidden_layer[i] = b1->hidden_layer[i];
	}
	output->hidden_bias = b1->hidden_bias;
	output->input_bias = b1->input_bias;
	return output;
}

float Population::Clamp01(float input)
{
	if (input > 1.0f)
		return 1.0f;
	else if (input < 0.0f)
		return 0.0f;
	return input;
}
