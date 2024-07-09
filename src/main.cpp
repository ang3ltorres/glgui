#include "pch.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "image.hpp"
#include "engine.hpp"
#include "widgets/button.hpp"

bool render = true;

void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {

	UNUSED(window);
	UNUSED(scancode);
	UNUSED(mods);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		render = true;

}

int main() {

	Engine::init();
	glfwSetKeyCallback(Engine::window, &key_callback);

	Texture txr1("../res/PNG_transparency_demonstration_1.png");
	Image img1(&txr1);

	glgui::widget::Button b1(50, 0, 50, 50, {50, 120, 255}, nullptr);


	while (!Engine::windowShouldClose()) {

		if (render) {

			Engine::processInput();
			Engine::clearScreen(255, 0, 255);

			Image::imageShader->use();
			Image::imageShader->setValue("projection", Engine::projection);

			img1.setPosition(img1.x + 1, img1.y);
			img1.draw();

			b1.draw();

			// Swap buffers and poll events
			glfwSwapBuffers(Engine::window);
			render = false;

		} else {

			// No mouse movement, continue polling events
			glfwWaitEventsTimeout(0.1);
			continue;
		}

		glfwPollEvents();
	}



	return Engine::end();
}
