#include "engine.hpp"
#include "image.hpp"

GLFWwindow *Engine::window;
std::uint32_t Engine::screenWidth;
std::uint32_t Engine::screenHeight;
glm::highp_mat4 Engine::projection;
glgui::Vec2 Engine::mousePos;

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {

	UNUSED(window);
	// glViewport(0, 0, width, height);
	Engine::projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
	glViewport(0, 0, width, height);
}


static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {

	UNUSED(window);

	Engine::mousePos.x = xpos;
	Engine::mousePos.y = ypos;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	UNUSED(window);
	UNUSED(mods);

	if (button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_PRESS)
		Engine::mouseClick = true;

	if (button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_RELEASE)
		Engine::mouseClick = false;

	// Check all clickable widgets
}



static void processInput(GLFWwindow *window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Engine::init() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);

	Engine::window = glfwCreateWindow(1280, 720, "GL Test", NULL, NULL);
	glfwMakeContextCurrent(Engine::window);
	glfwSwapInterval(1);
	glewInit();

	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetFramebufferSizeCallback(Engine::window, &framebuffer_size_callback);
	glfwSetCursorPosCallback(Engine::window, &cursor_pos_callback);
	glfwSetMouseButtonCallback(Engine::window, &mouse_button_callback);

	Engine::projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
	Engine::mousePos.x = 0.0f;
	Engine::mousePos.y = 0.0f;
	Engine::mouseClick = false;

	Image::init();
}

bool Engine::end() {

	glfwTerminate();
	return 0;
}

bool Engine::windowShouldClose() {

	return glfwWindowShouldClose(Engine::window);
}

void Engine::processInput() {

	::processInput(Engine::window);
}

void Engine::clearScreen(std::uint8_t r, std::uint8_t g, std::uint8_t b) {

	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
