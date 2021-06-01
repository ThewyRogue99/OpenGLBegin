#pragma once

#include "../Model.h"
#include "../textures/TextureAtlas.h"
#include "../Material.h"

class Cube : public Model
{
public:

	Cube(glm::vec3 pos = glm::vec3(0.f), glm::vec3 size = glm::vec3(1.f), glm::vec3 rotation = glm::vec3(0.f))
		: Model(pos, size, rotation) { }

	void init(std::string textureName, std::string textureSpecularName = "def") 
	{
		int nVertices = 36;

		std::vector<unsigned int> indices(nVertices);
		for (int i = 0; i < nVertices; i++)
			indices[i] = i;

		std::vector<Texture> textureList;

		Texture texDiffuse(textureName, aiTextureType_DIFFUSE);
		texDiffuse.load();

		textureList.push_back(texDiffuse);

		if (textureSpecularName != "def")
		{
			Texture texSpecular(textureSpecularName, aiTextureType_SPECULAR);
			texSpecular.load();

			textureList.push_back(texSpecular);
		}

		meshes.push_back(Mesh(Vertex::genList(vertices, nVertices), indices, textureList));

		Model::init();
	}

	void init(Material material)
	{
		int nVertices = 36;

		aiColor4D diffuse = aiColor4D(material.diffuse.x, material.diffuse.y, material.diffuse.z, 1.f);
		aiColor4D specular = aiColor4D(material.specular.x, material.specular.y, material.specular.z, 1.f);

		std::vector<unsigned int> indices(nVertices);
		for (int i = 0; i < nVertices; i++)
			indices[i] = i;

		meshes.push_back(Mesh(Vertex::genList(vertices, nVertices), indices, diffuse, specular));
		Model::init();
	}

	void init(TextureAtlas* textAtlas, std::vector<int> texIndexList) {
		textAtlas->load();

		int nVertices = 36;

		int index = 0;
		for (int texIndex : texIndexList)
		{
			std::vector<glm::vec2> texCoords = textAtlas->getTexCoordsByIndex(texIndex);
			
			int vertexLength = sizeof(Vertex) / sizeof(float);
			int addr = index * vertexLength + (vertexLength - 2);

			vertices[addr] = texCoords[1].x;
			vertices[addr + 1] = texCoords[1].y;
			addr += vertexLength;

			vertices[addr] = texCoords[2].x;
			vertices[addr + 1] = texCoords[2].y;
			addr += vertexLength;

			vertices[addr] = texCoords[3].x;
			vertices[addr + 1] = texCoords[3].y;
			addr += vertexLength;

			vertices[addr] = texCoords[3].x;
			vertices[addr + 1] = texCoords[3].y;
			addr += vertexLength;

			vertices[addr] = texCoords[0].x;
			vertices[addr + 1] = texCoords[0].y;
			addr += vertexLength;

			vertices[addr] = texCoords[1].x;
			vertices[addr + 1] = texCoords[1].y;
			addr += vertexLength;

			index += 6;
		}

		std::vector<unsigned int> indices(nVertices);
		for (int i = 0; i < nVertices; i++)
			indices[i] = i;

		meshes.push_back(Mesh(Vertex::genList(vertices, nVertices), indices, { *textAtlas }));

		Model::init();
	}

private:
	static float vertices[];
};

float Cube::vertices[] = {
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,

		 0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    0.0f, 0.0f,

		 0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 1.0f
};