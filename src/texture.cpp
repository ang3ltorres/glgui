#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <plutosvg.h>

static void RGBA(std::uint8_t *data, std::uint32_t width, std::uint32_t height) {

	std::uint8_t temp[4];
	for (std::uint32_t i = 0; i < (width * height * 4); i += 4) {

		temp[0] = data[i + 2];
		temp[1] = data[i + 1];
		temp[2] = data[i + 0];
		temp[3] = data[i + 3];

		std::memcpy(&data[i], temp, sizeof(std::uint8_t) * 4);
	}

	// for (std::uint32_t y = 0; y < height / 2; y++) {

	// 	for (std::uint32_t x = 0; x < width; x++) {

	// 		std::uint32_t topIndex = y * width * 4 + x * 4;
	// 		std::uint32_t bottomIndex = (height - 1 - y) * width * 4 + x * 4;

	// 		// Swap pixels using a temporary array
	// 		std::swap_ranges(&data[topIndex], &data[topIndex + 4], &data[bottomIndex]);
	// 	}
	// }
}

Texture::~Texture() {

	glDeleteTextures(1, &id);
}

Texture::Texture(const std::string &fileName) {

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);
	int comp;
	auto data = stbi_load(fileName.data(), &width, &height, &comp, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string &fileName, std::uint32_t width, std::uint32_t height)
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
	
	// Convert ARGB to RGBA and flip Vertically
	RGBA(data, width, height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	plutovg_surface_destroy(surface);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string &fileName, double dpi) {

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

Texture::Texture(std::uint32_t width, std::uint32_t height)
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
