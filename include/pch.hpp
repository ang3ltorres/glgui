#pragma once

#define UNUSED(expr) (void)(expr)

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <fmt/core.h>
#include <cstdint>
#include <cstring>
#include <new>
#include <memory>
#include <vector>
#include <algorithm>
#include <filesystem>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
