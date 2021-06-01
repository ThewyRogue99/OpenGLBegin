#pragma once

#include "../Model.h"

class Pyramid : public Model
{
public:
	glm::vec3 pos;
	glm::vec3 size;
	glm::vec3 rotation;

	Pyramid(glm::vec3 pos = glm::vec3(0.f), glm::vec3 size = glm::vec3(1.f), glm::vec3 rotation = glm::vec3(0.f))
		: Model(pos, size, rotation) { }

	void init(const char* textureName = "assets/textures/solid-white.png") {
		int nVertices = 16;

		float vertices[] = {
			-0.5f,  0.0f,  0.5f,   0.0f,  0.0f,
			 0.5f,  0.0f,  0.5f,   1.0f,  0.0f,
			 0.0f,  0.5f,  0.0f,   0.5f,  1.0f,

			 0.5f,  0.0f,  0.5f,   0.0f,  0.0f,
			 0.5f,  0.0f, -0.5f,   1.0f,  0.0f,
			 0.0f,  0.5f,  0.0f,   0.5f,  1.0f,

			 0.5f,  0.0f, -0.5f,   0.0f,  0.0f,
			-0.5f,  0.0f, -0.5f,   1.0f,  0.0f,
			 0.0f,  0.5f,  0.0f,   0.5f,  1.0f,

			-0.5f,  0.0f, -0.5f,   0.0f,  0.0f,
			-0.5f,  0.0f,  0.5f,   1.0f,  0.0f,
			 0.0f,  0.5f,  0.0f,   0.5f,  1.0f,

			-0.5f,  0.0f,  0.5f,   0.0f,  0.0f,
			 0.5f,  0.0f,  0.5f,   0.1f,  0.0f,
			 0.5f,  0.0f, -0.5f,   0.1f,  0.1f,
			-0.5f,  0.0f, -0.5f,   0.0f,  0.1f
		};

		std::vector<unsigned int> squareIndices = { 
			12, 14, 15,
			12, 13, 14
		};

		int safeSize = 12;

		std::vector<unsigned int> indices(safeSize);
		for (int i = 0; i < safeSize; i++)
			indices[i] = i;

		indices.insert(indices.end(), squareIndices.begin(), squareIndices.end());

		Texture tex1(textureName, aiTextureType_DIFFUSE);
		tex1.load();

		meshes.push_back(Mesh(Vertex::genList(vertices, nVertices), indices, { tex1 }));
	}

	virtual void render(Shader shader) override
	{
		glm::mat4 model = glm::mat4(1.f);

		glm::mat4 rotationMat = glm::rotate(glm::mat4(1.f), glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		rotationMat = glm::rotate(rotationMat, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		rotationMat = glm::rotate(rotationMat, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));

		model = glm::translate(model, pos);
		model = glm::scale(model, size);
		model = model * rotationMat;
		shader.setMat4("model", model);

		Model::render(shader);
	}
};