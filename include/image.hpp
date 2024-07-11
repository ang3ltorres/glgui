#pragma once

#include "pch.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "utils.hpp"

namespace glgui
{
	struct Image {

		static void init();
		static void end();
		static Shader *imageShader;

		Image(Texture *texture, float x = 0, float y = 0);
		Image(const Image& image) = delete;
		~Image() = default;

		void draw();
		
		Texture *texture;
		glm::mat4 model;

		glgui::Rect rect;

		void setSize(float width, float height);
		void setPosition(float x, float y);
	};
}
