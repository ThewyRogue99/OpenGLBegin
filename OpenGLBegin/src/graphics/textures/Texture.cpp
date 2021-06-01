#include "Texture.h"

#include "../../debug/debug.h"

int Texture::currentId = -1;

Texture::Texture() {}

Texture::Texture(std::string path, aiTextureType type, bool defaultParams)
	: path(path), type(type), id(++currentId), defaultParams(defaultParams) {

	generate();
}

void Texture::generate()
{
	glGenTextures(1, &tex);
}

void Texture::load(bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
	uint8_t* data = stbi_load(path.c_str(), &width, &height, &nChannels, 0);

	unsigned int colorType = 0;

	switch (nChannels)
	{
	case 1:
		colorType = GL_RED;
		break;
	case 3:
		colorType = GL_RGB;
		break;
	case 4:
		colorType = GL_RGBA;
		break;
	default:
		colorType = 0;
		break;
	}

	if (data && colorType != 0)
	{
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, colorType, width, height, 0, colorType, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		printError("Failed to load image at path: " + std::string(path));

	stbi_image_free(data);

	isLoaded = true;

	if (defaultParams)
	{
		setFilters(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		setWrap(GL_REPEAT);
	}
}

void Texture::setFilters(GLenum all) { setFilters(all, all); }

void Texture::setFilters(GLenum mag, GLenum min)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
}

void Texture::setWrap(GLenum all) { setWrap(all, all); }

void Texture::setWrap(GLenum s, GLenum t)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
}

void Texture::bind() { glActiveTexture(GL_TEXTURE0 + id); glBindTexture(GL_TEXTURE_2D, tex); }

glm::vec2 Texture::getTexCoordByPixel(int x, int y)
{
	if (x > width)
		return glm::vec2(0.f, 0.f);
	if (y > height)
		return glm::vec2(0.f, 0.f);

	return glm::vec2((float)x / (float)width, 1 - ((float)y / (float)height));
}