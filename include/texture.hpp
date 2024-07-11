#pragma once

#include "pch.hpp"

namespace glgui
{
	struct Texture {

		Texture() = delete;
		Texture(const Texture&) = delete;
		~Texture();

		Texture(const std::string &fileName);
		Texture(const std::string &fileName, std::uint32_t width, std::uint32_t height);
		Texture(const std::string &fileName, double dpi);
		Texture(const char *svgString, size_t size, std::uint32_t width, std::uint32_t height);
		Texture(std::uint32_t width, std::uint32_t height);

		GLuint id;
		std::int32_t width;
		std::int32_t height;
	};
}
