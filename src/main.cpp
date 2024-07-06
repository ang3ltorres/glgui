#include "pch.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "image.hpp"
#include "engine.hpp"
#include "widgets/button.hpp"

bool mouseMoved = false;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

	UNUSED(window);
	UNUSED(xpos);
	UNUSED(ypos);

	// Update mouse movement flag
	mouseMoved = true;
}

int main() {

	Engine::init();
	glfwSetCursorPosCallback(Engine::window, cursor_position_callback);

	Texture txr1("../res/PNG_transparency_demonstration_1.png");
	Image img1(&txr1);

	glgui::widget::Button b1(50, 0, 50, 50, {50, 120, 255}, nullptr);


	while (!Engine::windowShouldClose()) {


		if (mouseMoved) {

			Engine::processInput();
			Engine::clearScreen(255, 0, 255);

			Image::imageShader->use();
			Image::imageShader->setValue("projection", Engine::projection);

			img1.setPosition(img1.x + 1, img1.y);
			img1.draw();

			b1.draw();

			// Swap buffers and poll events
			glfwSwapBuffers(Engine::window);
			mouseMoved = false;

		} else {

			// No mouse movement, continue polling events
			glfwWaitEventsTimeout(0.1);
			continue;
		}

		glfwPollEvents();
	}



	return Engine::end();
}
