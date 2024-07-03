#pragma once

#include <cstdint>
#include <string>

namespace glgui
{
	struct Color
	{
		Color();
		Color(const Color &other);
		Color(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0, std::uint8_t a = 255);
		~Color() = default;

		std::string rgbString();

		std::uint8_t r;
		std::uint8_t g;
		std::uint8_t b;
		std::uint8_t a;
	};
}
