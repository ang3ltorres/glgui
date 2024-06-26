#include "pch.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "image.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);

	GLFWwindow *window = glfwCreateWindow(800, 800, "GL Test", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewInit();

	glViewport(0, 0, 800, 800);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);

	auto projection = glm::ortho(0.0f, 800.0f, 800.0f, 0.0f, -1.0f, 1.0f);

	Texture txr("../res/ISO_C++_Logo.svg", 800, 800);
	Image::init();
	Image img(&txr);
	img.setSize(800, 800);

	while (!glfwWindowShouldClose(window)) {

		process_input(window);

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Image::imageShader->use();
		Image::imageShader->setValue("projection", projection);

		img.setPosition(img.x, img.y + 1);
		img.draw();

		glUseProgram(0);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {

	UNUSED(window);
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
