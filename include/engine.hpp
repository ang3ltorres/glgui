#pragma once

#include "pch.hpp"
#include "utils.hpp"
#include "widgets/button.hpp"

namespace glgui
{
	struct Engine {

		static void init();
		static bool end();
		static bool windowShouldClose();
		static void processInput();
		static void clearScreen(const glgui::Color &color);

		Engine() = delete;
		Engine(const Engine &engine) = delete;
		~Engine() = delete;

		static GLFWwindow *window;
		static std::uint32_t screenWidth;
		static std::uint32_t screenHeight;
		static glm::highp_mat4 projection;

		static bool doRender;
		static glgui::Vec2 mousePos;
		static bool mouseClick;

		// TODO
		static std::vector<glgui::widget::Base*> widgets;
		static std::vector<glgui::widget::Button*> buttons;
	};
}

