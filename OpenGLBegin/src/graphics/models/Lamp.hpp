#pragma once

#include "Cube.hpp"
#include "../Light.h"

class Lamp : public Cube
{
public:
	PointLight pointLight;

	Lamp(glm::vec4 diffuse,
		glm::vec4 specular,
		float k0,
		float k1,
		float k2,
		glm::vec3 pos,
		glm::vec3 size)
		: pointLight(pos, k0, k1, k2, glm::vec4(diffuse.x / 3.f, diffuse.y / 3.f, diffuse.z / 3.f, 1.f), diffuse, specular),
		Cube(pos, size) { }

	void init()
	{
		Cube::init({ pointLight.ambient, pointLight.diffuse, pointLight.specular, 1.f });
	}

	virtual void BeginPlay() override
	{
		Object::BeginPlay();

		pointLight.SpawnObject();
	}

	virtual void Render(Shader& shader) override
	{
		Cube::Render(shader);
	}
};