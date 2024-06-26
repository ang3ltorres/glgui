#include "pch.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "image.hpp"
#include "engine.hpp"

int main() {

	Engine::init();

	Texture txr("../res/ISO_C++_Logo.svg", 1280, 720);
	Texture txr2("../res/PNG_transparency_demonstration_1.png");

	Image img(&txr);
	Image img2(&txr2);

	std::uint8_t g = 0;

	while (!Engine::windowShouldClose()) {

		Engine::processInput();
		Engine::clearScreen(255, g, 255);
		g += 10;

		Image::imageShader->use();
		Image::imageShader->setValue("projection", Engine::projection);

		img.setPosition(img.x, img.y);
		img.draw();

		img2.draw();
	}

	return Engine::end();
}
