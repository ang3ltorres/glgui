#include "utils.hpp"
#include <fmt/format.h>

// Struct Color
glgui::Color::Color()
: r(0), g(0), b(0), a(0) {}

glgui::Color::Color(const Color &other)
: r(other.r), g(other.g), b(other.b), a(other.a) {}

glgui::Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
: r(r), g(g), b(b), a(a) {}

std::string glgui::Color::rgbString() {

	return fmt::format("rgb({:d},{:d},{:d})", r, g, b);
}