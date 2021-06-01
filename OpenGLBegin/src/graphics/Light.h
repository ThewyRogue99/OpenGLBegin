#pragma once

#include <glm/glm.hpp>

#include "Shader.h"
#include <vector>

class Light
{
public:
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

	Light(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, std::string name)
		: ambient(ambient), diffuse(diffuse), specular(specular), name(name) {

		lightList.push_back(this);
	};

	virtual void render(Shader shader, int idx);

	static void renderAllLights(Shader shader);

	static void cleanAllLights();

protected:
	static std::vector<Light*> lightList;

	std::string name;
};

class PointLight : public Light
{
public:
	glm::vec3 position;

	// Attenuation constants
	float k0;
	float k1;
	float k2;

	PointLight(glm::vec3 position, float k0, float k1, float k2, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
		: position(position), k0(k0), k1(k1), k2(k2), Light(ambient, diffuse, specular, "pointLight") { }

	virtual void render(Shader shader, int idx) override;
};

class DirLight : public Light
{
public:
	glm::vec3 direction;

	DirLight(glm::vec3 direction, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
		: direction(direction), Light(ambient, diffuse, specular, "dirLight") { }

	virtual void render(Shader shader, int idx) override;
};

class SpotLight : public Light
{
public:
	glm::vec3 position;
	glm::vec3 direction;

	float width;

	// Attenuation constants
	float k0;
	float k1;
	float k2;

	SpotLight(glm::vec3 position, glm::vec3 direction, float width, float k0, float k1, float k2, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
		: position(position), direction(direction),
		width(width),
		k0(k0), k1(k1), k2(k2),
		Light(ambient, diffuse, specular, "spotLight") { }

	virtual void render(Shader shader, int idx) override;
};