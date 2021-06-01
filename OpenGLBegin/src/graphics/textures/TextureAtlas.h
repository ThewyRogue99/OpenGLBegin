#pragma once
#include "Texture.h"
#include <vector>
#include <glm/glm.hpp>

class TextureAtlas : public Texture
{
public:
	TextureAtlas();
	TextureAtlas(const char* path, int rowCount, int columnCount);

	virtual void load(bool flip = true) override;


	std::vector<glm::vec2> getTexCoordsByIndex(int index);

private:
	void generateTexCoords();

	std::vector<std::vector<glm::vec2>> texCoords;

	int rowCount;
	int columnCount;
};