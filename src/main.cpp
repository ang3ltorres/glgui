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

static void button_callback(void* data) {

	fmt::println("Button clicked");
}

int main() {

	glgui::Engine::init();
	glfwSetKeyCallback(glgui::Engine::window, &key_callback);

	glgui::Texture txr1("../res/PNG_transparency_demonstration_1.png");
	glgui::Image img1(&txr1);

	glgui::widget::Button b1({50, 0, 50, 50}, {50, 120, 255}, &button_callback);


	while (!glgui::Engine::windowShouldClose()) {

		if (true) {

			glgui::Engine::processInput();
			glgui::Engine::clearScreen(255, 0, 255);

			glgui::Image::imageShader->use();
			glgui::Image::imageShader->setValue("projection", glgui::Engine::projection);

			img1.setPosition(img1.rect.pos.x + 1, img1.rect.pos.y);
			img1.draw();

			// b1.draw();

			for (const auto &i : glgui::Engine::widgets)
				i->draw();

			// Swap buffers
			glfwSwapBuffers(glgui::Engine::window);
			render = false;

		} else {

			// No mouse movement, continue polling events
			glfwWaitEventsTimeout(0.1);
			continue;
		}

		glfwPollEvents();
	}

	return glgui::Engine::end();
}
