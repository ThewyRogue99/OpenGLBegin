#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <Windows.h>

#include "../engine/Object.h"
#include "Mesh.h"
#include "../io/debug.h"

#include "../physics/RigidBody.h"
#include "../physics/Environment.h"

class Model : public Object
{
public:
	glm::vec3 pos;
	glm::vec3 size;
	glm::vec3 rotation;

	RigidBody rigidbody;

	Model();

	Model(glm::vec3 pos = glm::vec3(0.f), glm::vec3 size = glm::vec3(1.f), glm::vec3 rotation = glm::vec3(0.f), bool noTex = false) :
		size(size), rotation(rotation), noTex(noTex) {

		rigidbody.position = pos;
	};

	void loadModel(std::string path);

	virtual void BeginPlay() override { Object::BeginPlay(); rigidbody.SpawnObject(); }

	virtual void Render(Shader shader) override;

	virtual void DestroyObject() override;

protected:
	bool noTex;

	std::vector<Mesh> meshes;
	std::string directory;

	std::vector<Texture> textures_loaded;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type);
};