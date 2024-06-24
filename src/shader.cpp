#include "shader.hpp"

static GLchar* readFile(const std::string &fileName) {

	auto fileSize = std::filesystem::file_size(fileName);
	GLchar *string = (GLchar*)operator new(sizeof(GLchar) * (fileSize + 1));
	string[fileSize] = '\0';
	std::fstream file{fileName, std::ios::binary | std::ios::in};
	file.read(reinterpret_cast<char*>(string), fileSize);
	file.close();
	return string;
}

Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader, const std::string &geometryShader) {

	std::string infoLog;
	infoLog.resize(1024);
	
	GLint success;

	// Vertex shader
	GLchar *codeVertex = readFile(vertexShader);
	GLuint VShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VShader, 1, &codeVertex, NULL);
	glCompileShader(VShader);
	operator delete(codeVertex);

	glGetShaderiv(VShader, GL_COMPILE_STATUS, &success);
	if (success)
		fmt::print("Compile Sucess: {:s}!\n", "Vertex Shader");
	else {
		glGetShaderInfoLog(VShader, 1024, NULL, infoLog.data());
		fmt::print("Vertex Shader error:\n{:s}\n", infoLog);
	}

	// Fragment shader
	GLchar *codeFragment = readFile(fragmentShader);
	GLuint FShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FShader, 1, &codeFragment, NULL);
	glCompileShader(FShader);
	operator delete(codeFragment);

	glGetShaderiv(FShader, GL_COMPILE_STATUS, &success);
	if (success)
		fmt::print("Compile Sucess: {:s}!\n", "Fragment Shader");
	else {
		glGetShaderInfoLog(FShader, 1024, NULL, infoLog.data());
		fmt::print("Fragment Shader error:\n{:s}\n", infoLog);
	}

	// Geometry shader (Optional)
	GLuint GShader = 0;
	if (!geometryShader.empty()) {
		
		GLchar *codeGeometry = readFile(geometryShader);
		GShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(GShader, 1, &codeGeometry, NULL);
		glCompileShader(GShader);
		operator delete(codeGeometry);

		glGetShaderiv(GShader, GL_COMPILE_STATUS, &success);
		if (success)
			fmt::print("Compile Sucess: {:s}!\n", "Geometry Shader");
		else {
			glGetShaderInfoLog(GShader, 1024, NULL, infoLog.data());
			fmt::print("Geometry Shader error:\n{:s}\n", infoLog);
		}
	}

	// Create program
	id = glCreateProgram();
	glAttachShader(id, VShader);
	glAttachShader(id, FShader);
	if (!geometryShader.empty())
		glAttachShader(id, GShader);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (success)
		std::cout << "Linking Sucess!\n";
	else {
		glGetProgramInfoLog(id, 1024, NULL, infoLog.data());
		fmt::print("Linking Shader error:\n{:s}\n", infoLog);			
	}

	// Free resources
	glDeleteShader(VShader);
	glDeleteShader(FShader);
	if (!geometryShader.empty())
		glDeleteShader(GShader);
}

void Shader::use() {

	glUseProgram(id);
}

template <> void Shader::setValue<glm::mat4>(const std::string &name, glm::mat4 v) { glUniformMatrix4fv(glGetUniformLocation(id, name.data()), 1, false, value_ptr(v)); }
template <> void Shader::setValue<glm::mat3>(const std::string &name, glm::mat3 v) { glUniformMatrix3fv(glGetUniformLocation(id, name.data()), 1, false, value_ptr(v)); }
template <> void Shader::setValue<glm::mat2>(const std::string &name, glm::mat2 v) { glUniformMatrix2fv(glGetUniformLocation(id, name.data()), 1, false, value_ptr(v)); }

template <> void Shader::setValue<glm::vec4>(const std::string &name, glm::vec4 v) { glUniform4fv(glGetUniformLocation(id, name.data()), 1, value_ptr(v)); }
template <> void Shader::setValue<glm::vec3>(const std::string &name, glm::vec3 v) { glUniform3fv(glGetUniformLocation(id, name.data()), 1, value_ptr(v)); }
template <> void Shader::setValue<glm::vec2>(const std::string &name, glm::vec2 v) { glUniform2fv(glGetUniformLocation(id, name.data()), 1, value_ptr(v)); }

template <> void Shader::setValue<int>(const std::string &name, int v) { glUniform1i(glGetUniformLocation(id, name.data()), v); }
template <> void Shader::setValue<float>(const std::string &name, float v) { glUniform1f(glGetUniformLocation(id, name.data()), v); }
template <> void Shader::setValue<unsigned int>(const std::string &name, unsigned int v) { glUniform1ui(glGetUniformLocation(id, name.data()), v); }

void Shader::setValue(const std::string &name, float x, float y, float z, float w) { glUniform4f(glGetUniformLocation(id, name.data()), x, y, z, w); }
void Shader::setValue(const std::string &name, float x, float y, float z) { glUniform3f(glGetUniformLocation(id, name.data()), x, y, z); }
void Shader::setValue(const std::string &name, float x, float y) { glUniform2f(glGetUniformLocation(id, name.data()), x, y); }
