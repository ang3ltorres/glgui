cmake_minimum_required(VERSION 3.28)

project(test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -pedantic -Wextra)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(glgui ${SOURCES})

target_link_directories(glgui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/build/lib")

target_include_directories(glgui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

if (WIN32)
	target_link_libraries(glgui PRIVATE glew32 glfw3 opengl32 plutosvg plutovg fmt)
endif()
