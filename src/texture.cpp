#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <plutosvg.h>

static void RGBA(std::uint8_t *data, std::uint32_t width, std::uint32_t height) {

	// Calculate total number of bytes to process
	std::size_t numBytes = width * height * 4;

	// Process in batches of 4 bytes
	for (std::size_t i = 0; i < numBytes; i += 4) {

		// Swap bytes directly
		std::uint8_t temp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = temp;
	}
}

glgui::Texture::~Texture() {

	glDeleteTextures(1, &id);
}

glgui::Texture::Texture(const std::string &fileName) {

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(false);
	int comp;
	auto data = stbi_load(fileName.data(), &width, &height, &comp, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

glgui::Texture::Texture(const std::string &fileName, std::uint32_t width, std::uint32_t height)
: width(width), height(height) {

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Get data in ARGB format
	auto surface = plutosvg_load_from_file(fileName.data(), nullptr, width, height, 1.0f);
	std::uint8_t *data = plutovg_surface_get_data(surface);
	
	// Convert ARGB to RGBA
	RGBA(data, width, height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	plutovg_surface_destroy(surface);
	glBindTexture(GL_TEXTURE_2D, 0);
}

glgui::Texture::Texture(const std::string &fileName, double dpi) {

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Get data in ARGB format
	auto surface = plutosvg_load_from_file(fileName.data(), nullptr, 0, 0, dpi);
	std::uint8_t *data = plutovg_surface_get_data(surface);

	// Get width and height
	width = plutovg_surface_get_width(surface);
	height = plutovg_surface_get_height(surface);
	
	// Convert ARGB to RGBA
	RGBA(data, width, height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	plutovg_surface_destroy(surface);
	glBindTexture(GL_TEXTURE_2D, 0);
}

glgui::Texture::Texture(const char *svgString, size_t size, std::uint32_t width, std::uint32_t height)
: width(width), height(height) {

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Get data in ARGB format

	auto surface = plutosvg_load_from_memory(svgString, size, nullptr, width, height, 0);
	std::uint8_t *data = plutovg_surface_get_data(surface);
	
	// Convert ARGB to RGBA
	RGBA(data, width, height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	plutovg_surface_destroy(surface);
	glBindTexture(GL_TEXTURE_2D, 0);
}

glgui::Texture::Texture(std::uint32_t width, std::uint32_t height)
: width(width), height(height) {

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glBindTexture(GL_TEXTURE_2D, 0);
}
