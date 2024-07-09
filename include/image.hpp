#pragma once

#include "pch.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "utils.hpp"

struct Image {

	static void init();
	static void end();
	static Shader *imageShader;

	Image(Texture *texture, std::int32_t x = 0, std::int32_t y = 0);
	Image(const Image& image) = delete;
	~Image() = default;

	void draw();
	
	Texture *texture;
	glm::mat4 model;

	glgui::Rect rect;

	void setSize(std::int32_t width, std::int32_t height);
	void setPosition(std::int32_t x, std::int32_t y);
};
