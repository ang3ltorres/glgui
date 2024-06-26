#include "pch.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "image.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);
glm::highp_mat4 projection;

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);

	GLFWwindow *window = glfwCreateWindow(800, 600, "GL Test", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewInit();

	glViewport(0, 0, 800, 600);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);

	projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

	Texture txr("../res/ISO_C++_Logo.svg", 800, 600);
	Texture txr2("../res/PNG_transparency_demonstration_1.png");

	Image::init();

	Image img(&txr);
	img.setSize(400, 400);

	Image img2(&txr2);
	img2.setSize(400, 400);

	while (!glfwWindowShouldClose(window)) {

		process_input(window);

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Image::imageShader->use();
		Image::imageShader->setValue("projection", projection);

		img.setPosition(img.x, img.y);
		img.draw();

		img2.draw();

		glUseProgram(0);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {

	UNUSED(window);
	// glViewport(0, 0, width, height);
	projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
