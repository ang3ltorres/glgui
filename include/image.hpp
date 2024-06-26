#pragma once

#include "pch.hpp"
#include "texture.hpp"
#include "shader.hpp"

struct Image {

	static void init();
	static void end();
	static Shader *imageShader;

	Image(Texture *texture);
	Image(const Image& image) = delete;
	~Image();

	void draw();
	
	Texture &texture;
	glm::mat4 model;

	std::int32_t x;
	std::int32_t y;

	std::int32_t width;
	std::int32_t height;

	void setSize(std::int32_t width, std::int32_t height);
	void setPosition(std::int32_t x, std::int32_t y);
};
