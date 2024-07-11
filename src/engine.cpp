#include "engine.hpp"
#include "image.hpp"

GLFWwindow *glgui::Engine::window;
std::uint32_t glgui::Engine::screenWidth;
std::uint32_t glgui::Engine::screenHeight;
glm::highp_mat4 glgui::Engine::projection;

bool glgui::Engine::doRender;
glgui::Vec2 glgui::Engine::mousePos;
bool glgui::Engine::mouseClick;

std::vector<glgui::widget::Base*> glgui::Engine::widgets;
std::vector<glgui::widget::Button*> glgui::Engine::buttons;

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {

	UNUSED(window);
	// glViewport(0, 0, width, height);
	glgui::Engine::projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
	glViewport(0, 0, width, height);
	glgui::Engine::doRender = true;
}


static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {

	UNUSED(window);

	glgui::Engine::mousePos.x = xpos;
	glgui::Engine::mousePos.y = ypos;
	glgui::Engine::doRender = true;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	UNUSED(window);
	UNUSED(mods);

	if (button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_PRESS)
		glgui::Engine::mouseClick = true;

	if (button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_RELEASE)
		glgui::Engine::mouseClick = false;

	// Check all clickable widgets
	if (button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_PRESS) {

		for (const auto &i : glgui::Engine::buttons) {

			if (i->rect.collision(glgui::Engine::mousePos))
				i->callbackClick(nullptr);
		}
	}
}

static void processInput(GLFWwindow *window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void glgui::Engine::init() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	glgui::Engine::window = glfwCreateWindow(1280, 720, "GL Test", NULL, NULL);
	glfwMakeContextCurrent(glgui::Engine::window);
	glfwSwapInterval(1);
	glewInit();

	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetFramebufferSizeCallback(glgui::Engine::window, &framebuffer_size_callback);
	glfwSetCursorPosCallback(glgui::Engine::window, &cursor_pos_callback);
	glfwSetMouseButtonCallback(glgui::Engine::window, &mouse_button_callback);

	glgui::Engine::projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);

	glgui::Engine::doRender = true;
	glgui::Engine::mousePos.x = 0.0f;
	glgui::Engine::mousePos.y = 0.0f;
	glgui::Engine::mouseClick = false;

	glgui::Image::init();
}

bool glgui::Engine::end() {

	glfwTerminate();
	return 0;
}

bool glgui::Engine::windowShouldClose() {

	return glfwWindowShouldClose(glgui::Engine::window);
}

void glgui::Engine::processInput() {

	::processInput(glgui::Engine::window);
}

void glgui::Engine::clearScreen(std::uint8_t r, std::uint8_t g, std::uint8_t b) {

	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
