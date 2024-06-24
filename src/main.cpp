#include "pch.hpp"
#include "shader.hpp"
#include "texture.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

static const float vertices[] = {

	// Vertices			// Color			// Texture coords
	0.000f, 0.000f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
	0.000f, 800.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
	800.0f, 800.0f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
	800.0f, 0.000f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f
};

static const GLuint indices[] = {

	0, 1, 3,
	1, 2, 3
};

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
	auto model = glm::mat4(1.0f);
	
	Shader shader("../res/shaders/vertex.vert", "../res/shaders/fragment.frag", "../res/shaders/geometry.geom");
	shader.setValue("image", 0);

	Texture txr("../res/ISO_C++_Logo.svg", 800, 800);

	///////////////////////
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// Indices Data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// VBO Data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 0));
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 2));
	glEnableVertexAttribArray(1);

	// Texture Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 5));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) {

		process_input(window);

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));

		shader.use();
		shader.setValue("projection", projection);
		shader.setValue("model", model);
		
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, txr.id);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
		glBindVertexArray(0);
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
