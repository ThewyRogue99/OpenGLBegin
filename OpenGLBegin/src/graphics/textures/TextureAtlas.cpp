#include "TextureAtlas.h"
#include <iostream>

TextureAtlas::TextureAtlas() { }

TextureAtlas::TextureAtlas(const char* path, int rowCount, int columnCount)
	: rowCount(rowCount), columnCount(columnCount), Texture(path, aiTextureType_DIFFUSE, false) {
	
	generate();
}

void TextureAtlas::load(bool flip) 
{ 
	if (!isLoaded)
	{
		Texture::load();
		setFilters(GL_NEAREST, GL_NEAREST_MIPMAP_NEAREST);
		setWrap(GL_REPEAT);
		generateTexCoords();
	}
}

void TextureAtlas::generateTexCoords()
{
	int sizeX = width / rowCount;
	int sizeY = height / columnCount;

	for (int y = 0; y < height; y += sizeY)
	{
		for (int x = 0; x < width; x += sizeX)
		{
			std::vector<glm::vec2> result(4);

			result[0] = getTexCoordByPixel(x, y);
			result[1] = getTexCoordByPixel(x, y + sizeY);
			result[2] = getTexCoordByPixel(x + sizeX, y + sizeY);
			result[3] = getTexCoordByPixel(x + sizeX, y);

			texCoords.push_back(result);
		}
	}
}

std::vector<glm::vec2> TextureAtlas::getTexCoordsByIndex(int index) { return texCoords[index]; }
