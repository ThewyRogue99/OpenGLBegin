#pragma once

#include <glm/glm.hpp>

#include "Shader.h"
#include "Object.h"
#include <vector>

enum class LightType
{
	PointLight,
	DirLight,
	SpotLight
};

class Light : public Object
{
public:
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

	Light(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, LightType lightType)
		: ambient(ambient), diffuse(diffuse), specular(specular), lightType(lightType) {

		if (lightType == LightType::PointLight)
			pointLightList.push_back(this);
		else if (lightType == LightType::DirLight)
			dirLightList.push_back(this);
		else if (lightType == LightType::SpotLight)
			spotLightList.push_back(this);
	};

	virtual void Render(Shader shader) override;

protected:
	static std::vector<Light*> pointLightList;
	static std::vector<Light*> dirLightList;
	static std::vector<Light*> spotLightList;

	LightType lightType;

	int getIndex();

	std::string getTypeName();

	std::string getFullName()
		{ return std::string(getTypeName() + '[' + std::to_string(getIndex()) + ']'); }
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
		: position(position), k0(k0), k1(k1), k2(k2), Light(ambient, diffuse, specular, LightType::PointLight) { }

	virtual void Render(Shader shader) override;
};

class DirLight : public Light
{
public:
	glm::vec3 direction;

	DirLight(glm::vec3 direction, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
		: direction(direction), Light(ambient, diffuse, specular, LightType::DirLight) { }

	virtual void Render(Shader shader) override;
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
		Light(ambient, diffuse, specular, LightType::SpotLight) { }

	virtual void Render(Shader shader) override;
};