#pragma once

#include "pch.hpp"

struct Shader {

	Shader() = delete;
	Shader(const Shader&) = delete;

	GLuint id;
	Shader(const std::string &vertexShader, const std::string &fragmentShader, const std::string &geometryShader = "");
	void use();

	template <typename T> void setValue(const std::string &name, T v);
	void setValue(const std::string &name, float x, float y, float z, float w);
	void setValue(const std::string &name, float x, float y, float z);
	void setValue(const std::string &name, float x, float y);
};
