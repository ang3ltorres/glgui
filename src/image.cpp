#include "image.hpp"

Shader *Image::imageShader = nullptr;

static GLuint VAO;
static GLuint VBO;
static GLuint EBO;

static const GLfloat vertices[] = {

	// Vertices			// Color			// Texture coords
	0.000f, 0.000f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
	0.000f, 1.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
	1.0f, 	1.0f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
	1.0f, 	0.000f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f
};

static const GLuint indices[] = {

	0, 1, 3,
	1, 2, 3
};
	
void Image::init() {

	Image::imageShader = new Shader("../res/shaders/image.vert", "../res/shaders/image.frag", "../res/shaders/image.geom");
	Image::imageShader->setValue("image", 0);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// EBO Indices Data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	// VBO Data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

		// Vertices
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(sizeof(float) * 0));
		glEnableVertexAttribArray(0);

		// Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(sizeof(float) * 2));
		glEnableVertexAttribArray(1);

		// Texture Coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(sizeof(float) * 5));
		glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Image::end() {

	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	delete Image::imageShader;
}

Image::Image(Texture *texture, float x, float y)
: texture(texture), model(glm::mat4(1.0f)), rect({x, y}, {(float)texture->width, (float)texture->height}) {

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(rect.pos.x, rect.pos.y, 0.0f));
	model = glm::scale(model, glm::vec3(rect.size.x, rect.size.y, 0.0f));
}

void Image::draw() {

	Image::imageShader->setValue("model", model);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0));
	glBindVertexArray(0);
}

void Image::setSize(float width, float height) {

	rect.size.x = width;
	rect.size.y = height;

	model = glm::scale(model, glm::vec3(width, height, 0.0f));

	// GLfloat vertices[] = {

	// 	// Vertices							// Color			// Texture coords
	// 	0.000f, 		0.000f,				1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
	// 	0.000f, 		(float)height,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
	// 	(float)width, 	(float)height,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
	// 	(float)width, 	0.000f,				1.0f, 1.0f, 1.0f,	1.0f, 0.0f
	// };

	// glNamedBufferData(VBO, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

void Image::setPosition(float x, float y) {

	rect.pos.x = x;
	rect.pos.y = y;

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(rect.pos.x, rect.pos.y, 0.0f));
	model = glm::scale(model, glm::vec3(rect.size.x, rect.size.y, 0.0f));
}


