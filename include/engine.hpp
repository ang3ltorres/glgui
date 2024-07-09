#pragma once

#include "pch.hpp"

struct Engine {

	static void init();
	static bool end();
	static bool windowShouldClose();
	static void processInput();
	static void clearScreen(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0);

	Engine() = delete;
	Engine(const Engine &engine) = delete;
	~Engine() = delete;

	static GLFWwindow *window;
	static std::uint32_t screenWidth;
	static std::uint32_t screenHeight;
	static glm::highp_mat4 projection;

	static std::int32_t mousePosX;
	static std::int32_t mousePosY;
};
