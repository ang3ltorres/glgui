#pragma once

#include <cstdint>
#include <string>

namespace glgui
{
	struct Color {

		Color();
		Color(const Color &other);
		Color(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0, std::uint8_t a = 255);
		~Color() = default;

		std::string rgbString();
		std::string rgbaString();

		std::uint8_t r;
		std::uint8_t g;
		std::uint8_t b;
		std::uint8_t a;
	};

	struct Vec2 {

		Vec2();
		Vec2(const Vec2 &other);
		Vec2(float x, float y);
		~Vec2() = default;

		float x;
		float y;
	};

	struct Rect {

		Rect();
		Rect(const Rect &other);
		Rect(float x, float y, float w, float h);
		Rect(const Vec2 &pos, const Vec2 &size);
		~Rect() = default;

		Vec2 pos;
		Vec2 size;

		bool collision(Vec2 pos);
	};
}
