#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <assimp/scene.h>

#include <stb/stb_image.h>
#include <string>

class Texture
{
public:
	Texture();
	Texture(std::string path, aiTextureType type, bool defaultParams = true);

	void generate();
	virtual void load(bool flip = true);

	void setFilters(GLenum all);
	void setFilters(GLenum s, GLenum t);

	void setWrap(GLenum all);
	void setWrap(GLenum s, GLenum t);

	void bind();

	unsigned int id;
	unsigned int tex;
	aiTextureType type;
	std::string path;

protected:
	int nChannels;
	int width;
	int height;

	bool isLoaded = false;

	glm::vec2 getTexCoordByPixel(int x, int y);

private:
	static int currentId;
	bool defaultParams = false;
};

enum class MaterialType
{
	MATERIAL_TYPE_MATERIAL = 1,
	MATERIAL_TYPE_TEXTURE,
	MATERIAL_TYPE_ATLAS
};