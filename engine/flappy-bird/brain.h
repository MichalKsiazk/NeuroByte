#pragma once

#include "transform.h"
#include <vector>
#include <math.h>
#include <iostream>


class Brain
{
public:
	Brain(Transform* parentBirdTransform, float* horizontalDst, float* nextPipeHeight);
	~Brain();

	bool Update(float *score);
	bool Output();

	Transform* parentBirdTransform;
	float* nextPipeHeight;
	float* horizontalDst;

	float fitness;
	float VerticalDst();

	float input_layer[2][4];
	float hidden_layer[4];
	float output;
	float trigger;
	float range;

	float RandomWeight(float min, float max);

	void InitInputLayer();
	void InitHiddenLayer();
	float input_bias;
	float hidden_bias;
private:

	float Sigmoid(float input);

};

