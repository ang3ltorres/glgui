#include "utils.hpp"
#include <fmt/format.h>

// Struct Color
glgui::Color::Color()
: r(0), g(0), b(0), a(0) {}

glgui::Color::Color(const Color &other)
: r(other.r), g(other.g), b(other.b), a(other.a) {}

glgui::Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
: r(r), g(g), b(b), a(a) {}

std::string glgui::Color::rgbString() {

	return fmt::format("rgb({:d},{:d},{:d})", r, g, b);
}

std::string glgui::Color::rgbaString() {
	
	return fmt::format("rgba({:d},{:d},{:d},{:d})", r, g, b, a);
}

// Struct Vec2
glgui::Vec2::Vec2()
: x(0.0f), y(0.0f) {}

glgui::Vec2::Vec2(const Vec2 &other)
: x(other.x), y(other.y) {}

glgui::Vec2::Vec2(float x, float y)
: x(x), y(y) {}

// Struct Rect
glgui::Rect::Rect()
: pos(0.0f, 0.0f), size(0.0f, 0.0f) {}

glgui::Rect::Rect(const Rect &other)
: pos(other.pos), size(other.size) {}

glgui::Rect::Rect(float x, float y, float w, float h)
: pos(x, y), size(w, h) {}

glgui::Rect::Rect(const Vec2 &pos, const Vec2 &size)
: pos(pos), size(size) {}

bool glgui::Rect::collision(Vec2 pos) {

	return (
		pos.x >= this->pos.x and pos.x <= this->pos.x + this->size.x
		and
		pos.y >= this->pos.y and pos.y <= this->pos.y + this->size.y
	);
}
