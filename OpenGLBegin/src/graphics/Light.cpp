#include "Light.h"

std::vector<Light*> Light::lightList = { };

void Light::render(Shader shader, int idx)
{
	std::string fullname = name + '[' + std::to_string(idx) + ']';

	shader.set4Float(fullname + ".ambient", ambient);
	shader.set4Float(fullname + ".diffuse", diffuse);
	shader.set4Float(fullname + ".specular", specular);
}

void Light::renderAllLights(Shader shader)
{
	std::vector<Light*> pointLightList;
	std::vector<Light*> dirLightList;
	std::vector<Light*> spotLightList;

	for (Light* light : lightList)
	{
		if (light->name == "pointLight")
			pointLightList.push_back(light);
		else if (light->name == "dirLight")
			dirLightList.push_back(light);
		else if (light->name == "spotLight")
			spotLightList.push_back(light);
	}

	shader.Activate();

	int pointLightCount = (int)pointLightList.size();
	int dirLightCount = (int)dirLightList.size();
	int spotLightCount = (int)spotLightList.size();

	shader.setInt("pointLightCount", pointLightCount);
	shader.setInt("dirLightCount", dirLightCount);
	shader.setInt("spotLightCount", spotLightCount);

	// Render Point Lights
	for (int i = 0; i < pointLightCount; i++)
	{
		Light* pointLight = pointLightList[i];
		pointLight->render(shader, i);
	}

	// Render Dir Lights
	for (int i = 0; i < dirLightCount; i++)
	{
		Light* dirLight = dirLightList[i];
		dirLight->render(shader, i);
	}

	// Render Spot Lights
	for (int i = 0; i < spotLightCount; i++)
	{
		Light* spotLight = spotLightList[i];
		spotLight->render(shader, i);
	}

	pointLightList.clear();
	dirLightList.clear();
	spotLightList.clear();
}

void Light::cleanAllLights()
{
	lightList.clear();
}

void PointLight::render(Shader shader, int idx)
{
	std::string fullname = name + '[' + std::to_string(idx) + ']';

	shader.Activate();

	shader.set3Float(fullname + ".position", position);

	shader.setFloat(fullname + ".k0", k0);
	shader.setFloat(fullname + ".k1", k1);
	shader.setFloat(fullname + ".k2", k2);

	Light::render(shader, idx);
}

void DirLight::render(Shader shader, int idx)
{
	std::string fullname = name + '[' + std::to_string(idx) + ']';

	shader.Activate();

	shader.set3Float(fullname + ".direction", direction);

	Light::render(shader, idx);
}

void SpotLight::render(Shader shader, int idx)
{
	std::string fullname = name + '[' + std::to_string(idx) + ']';

	shader.Activate();

	shader.set3Float(fullname + ".position", position);
	shader.set3Float(fullname + ".direction", direction);

	float cutOff = glm::cos(glm::radians(width * 0.625f));
	float outerCutOff = glm::cos(glm::radians(width));

	shader.setFloat(fullname + ".cutOff", cutOff);
	shader.setFloat(fullname + ".outerCutOff", outerCutOff);

	shader.setFloat(fullname + ".k0", k0);
	shader.setFloat(fullname + ".k1", k1);
	shader.setFloat(fullname + ".k2", k2);

	Light::render(shader, idx);
}