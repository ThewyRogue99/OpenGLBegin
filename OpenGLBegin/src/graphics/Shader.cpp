#include "Shader.h"

Shader::Shader() : id(0) { }

Shader::Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
{
	generate(vertexShaderFilePath, fragmentShaderFilePath);
}

void Shader::generate(const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
{
	unsigned int vertexShader = compileShader(vertexShaderFilePath, GL_VERTEX_SHADER);
	unsigned int fragmentShader = compileShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);

	id = glCreateProgram();

	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	//Catch errors
	GLint success = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		char infoLog[512];
		glGetProgramInfoLog(id, 512, NULL, infoLog);

		printError("Failed to run shader.\nLog: " + std::string(infoLog));
		id = 0;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

unsigned int Shader::compileShader(const char* filepath, int type)
{
	std::ifstream file;
	unsigned int shaderAddress = 0;

	file.open(filepath);

	if (file.is_open())
	{
		//Compile shader
		std::string str = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		shaderAddress = glCreateShader(type);
		const GLchar* fileStr = str.c_str();
		glShaderSource(shaderAddress, 1, &fileStr, NULL);
		glCompileShader(shaderAddress);

		//Catch errors
		GLint success = 0;
		glGetShaderiv(shaderAddress, GL_COMPILE_STATUS, &success);
		if (success == 0)
		{
			char infoLog[512];
			glGetShaderInfoLog(shaderAddress, 512, NULL, infoLog);
			printError("Failed to compile shader.\nLog: " + std::string(infoLog));
			shaderAddress = 0;
		}
	}
	else
		printError("Failed to open shader file in: " + std::string(filepath));

	file.close();

	return shaderAddress;
}

void Shader::Activate()
{
	glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set3Float(const std::string& name, float v1, float v2, float v3) {
	glUniform3f(glGetUniformLocation(id, name.c_str()), v1, v2, v3);
}

void Shader::set3Float(const std::string& name, glm::vec3 v) {
	glUniform3f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z);
}

void Shader::set4Float(const std::string& name, float v1, float v2, float v3, float v4) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), v1, v2, v3, v4);
}

void Shader::set4Float(const std::string& name, glm::vec4 v) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z, v.w);
}

void Shader::set4Float(const std::string& name, aiColor4D color) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), color.r, color.g, color.b, color.a);
}

void Shader::setMat3(const std::string& name, glm::mat3 val) {
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setMat4(const char* name, glm::mat4 val)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(val));
}