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

#include "Object.h"
#include "Mesh.h"
#include "../debug/debug.h"

class Model : public Object
{
public:
	glm::vec3 pos;
	glm::vec3 size;
	glm::vec3 rotation;

	Model();

	Model(glm::vec3 pos = glm::vec3(0.f), glm::vec3 size = glm::vec3(1.f), glm::vec3 rotation = glm::vec3(0.f), bool noTex = false) :
		pos(pos), size(size), rotation(rotation), noTex(noTex) { };

	void init();
	void loadModel(std::string path);

	virtual void render(Shader shader);

	static void renderAllModels(Shader shader);

	static void cleanAllModels();

	void cleanup();

protected:
	bool noTex;

	std::vector<Mesh> meshes;
	std::string directory;

	std::vector<Texture> textures_loaded;

	static std::vector<Model*> modelList;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type);
};