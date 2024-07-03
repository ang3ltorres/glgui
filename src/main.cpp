#include "pch.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "image.hpp"
#include "engine.hpp"
#include "widgets/button.hpp"

int main() {

	Engine::init();

	Texture txr1("../res/PNG_transparency_demonstration_1.png");
	Image img1(&txr1);

	glgui::widget::Button b1(50, 0, 50, 50, {50, 120, 255}, nullptr);


	while (!Engine::windowShouldClose()) {

		Engine::processInput();
		Engine::clearScreen(255, 0, 255);

		Image::imageShader->use();
		Image::imageShader->setValue("projection", Engine::projection);

		img1.setPosition(img1.x + 1, img1.y);
		img1.draw();

		b1.draw();
	}

	return Engine::end();
}
