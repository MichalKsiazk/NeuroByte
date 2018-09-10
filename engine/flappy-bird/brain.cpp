#include "stdafx.h"
#include "brain.h"

Brain::Brain(Transform* parentBirdTransform, float* horizontalDst, float* nextPipeHeight)
{
	this->parentBirdTransform = parentBirdTransform;
	this->horizontalDst = horizontalDst;
	this->nextPipeHeight = nextPipeHeight;

	InitInputLayer();
	InitHiddenLayer();
	trigger = 0.8f;
	range = RandomWeight(0.0f, 0.15f);
}


Brain::~Brain()
{
}

bool Brain::Update(float *score)
{
	output = 0;
	float hidden_node[4];

	for (int h = 0; h < 4; h++)
	{
		hidden_node[h] = Sigmoid(input_bias + input_layer[0][h] * *horizontalDst + input_layer[1][h] * VerticalDst());
	}
	for (int n = 0; n < 4; n++)
	{
		output += hidden_layer[n] * hidden_node[n];
	}
	output = Sigmoid(hidden_bias + output);
	fitness = *score - *horizontalDst;
	return output >= trigger && output <= trigger + 0.03f;
}

bool Brain::Output()
{
	return false;
}

float Brain::VerticalDst()
{
	return parentBirdTransform->position.y - *nextPipeHeight;
}

float Brain::RandomWeight(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

void Brain::InitInputLayer()
{
	input_bias = RandomWeight(0.0, 1.0f);
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			input_layer[x][y] = RandomWeight(0.0, 1.0f);
		}
	}
}

void Brain::InitHiddenLayer()
{
	hidden_bias = RandomWeight(0.0, 1.0f);
	for (int x = 0; x < 4; x++)
	{
		hidden_layer[x] = RandomWeight(0.0, 1.0f);
	}
}

float Brain::Sigmoid(float input)
{
	float output = 1 / (1 + std::exp(-input));

	//std::cout << output << std::endl;

	return output;
}
