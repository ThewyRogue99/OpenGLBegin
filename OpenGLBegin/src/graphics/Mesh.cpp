#include "Mesh.h"

std::vector<Vertex> Vertex::genList(float* vertices, int nVertices)
{
	std::vector<Vertex> ret(nVertices);

	int stride = sizeof(Vertex) / sizeof(float);

	for (int i = 0; i < nVertices; i++)
	{
		ret[i].pos = glm::vec3(
			vertices[i * stride],
			vertices[i * stride + 1],
			vertices[i * stride + 2]
		);

		ret[i].normal = glm::vec3(
			vertices[i * stride + 3],
			vertices[i * stride + 4],
			vertices[i * stride + 5]
		);

		ret[i].texCoord = glm::vec2(
			vertices[i * stride + 6],
			vertices[i * stride + 7]
		);
	}

	return ret;
}

Mesh::Mesh() { }

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	: vertices(vertices), indices(indices), textures(textures), noTex(false) {
	
	setup();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, aiColor4D diffuse, aiColor4D specular)
	: vertices(vertices), indices(indices), diffuse(diffuse), specular(specular), noTex(true) {

	setup();
}

void Mesh::render(Shader shader)
{
	if (noTex)
	{
		shader.set4Float("material.diffuse", diffuse);
		shader.set4Float("material.specular", specular);
		shader.setBool("noTex", true);
	}
	else
	{
		shader.setBool("noTex", false);

		unsigned int diffuseIdx = 0;
		unsigned int specularIdx = 0;

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			Texture tex = textures[i];
			glActiveTexture(GL_TEXTURE0 + tex.id);

			std::string name;
			switch (tex.type)
			{
			case aiTextureType_DIFFUSE:
				name = "diffuse" + std::to_string(diffuseIdx++);
				break;
			case aiTextureType_SPECULAR:
				name = "specular" + std::to_string(specularIdx++);
				break;
			}
			shader.setInt(name, tex.id);

			tex.bind();
		}
	}

	shader.setFloat("material.shininess", 0.5f);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(0);
}

void Mesh::cleanup()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::setup()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bind VAO
	glBindVertexArray(VAO);

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Set attribute pointers

	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(0);

	//Normal vectors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	//Texture Coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}