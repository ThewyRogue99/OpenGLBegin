#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/scene.h>

#include <fstream>
#include <string>
#include "../io/debug.h"

class Shader
{
public:
	unsigned int id;

	Shader();
	Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

	void generate(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

	unsigned int compileShader(const char* filePath, int shaderType);

	void Activate();

	void setBool(const std::string& name, bool value);

	void setInt(const std::string& name, int value);

	void setFloat(const std::string& name, float value);

	void set3Float(const std::string& name, float v1, float v2, float v3);

	void set3Float(const std::string& name, glm::vec3 v);

	void set4Float(const std::string& name, float v1, float v2, float v3, float v4);

	void set4Float(const std::string& name, glm::vec4 v);

	void set4Float(const std::string& name, aiColor4D color);

	void setMat3(const std::string& name, glm::mat3 val);

	void setMat4(const char* name, glm::mat4 val);
};