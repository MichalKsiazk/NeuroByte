#include "stdafx.h"
#include "texture.h"




Texture::Texture(const std::string& filename)
{
	this->textureID = GenTexture(filename);
}

Texture::~Texture()
{
}

unsigned int Texture::GenTexture(const std::string& filename)
{

	std::cout << filename << std::endl;

	cv::Mat image = cv::imread(filename, cv::IMREAD_UNCHANGED);

	width = image.cols;
	height = image.rows;

	if (!image.data)                              
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	unsigned int output = 0;
	glGenTextures(1, &output);

	glBindTexture(GL_TEXTURE_2D, output);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	cv::flip(image, image, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, image.cols, image.rows, 0, GL_BGRA, GL_UNSIGNED_BYTE, image.ptr());

	glBindTexture(GL_TEXTURE_2D, 0);
	glGenerateMipmap(GL_TEXTURE_2D);

	return output;
}

void Texture::UseTexture(bool state)
{
	glActiveTexture(GL_TEXTURE0);
	if (state)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Texture::EnableTextures(bool state)
{
	if (state)
	{
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
}

glm::vec2 Texture::TextureRatio(float scale)
{
	return glm::vec2((float)width * 0.01f * scale, (float) height * 0.01f * scale);
}

