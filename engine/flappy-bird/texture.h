#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>


#include <glm/vec2.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class Texture
{
public:
	Texture(const std::string& filename);
	Texture()
	{

	}
	~Texture();

	unsigned int textureID;

	unsigned int width, height;

	unsigned int GenTexture(const std::string& filename);

	void UseTexture(bool state);
	void EnableTextures(bool state);

	glm::vec2 TextureRatio(float scale);

};

