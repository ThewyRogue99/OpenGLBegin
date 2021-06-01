#include "Light.h"

std::vector<Light*> Light::pointLightList = { };
std::vector<Light*> Light::dirLightList = { };
std::vector<Light*> Light::spotLightList = { };

void Light::Render(Shader shader)
{
	int lightIndex = getIndex();
	if (lightIndex == -1) return;

	shader.Activate();

	int pointLightCount = (int)pointLightList.size();
	int dirLightCount = (int)dirLightList.size();
	int spotLightCount = (int)spotLightList.size();

	shader.setInt("pointLightCount", pointLightCount);
	shader.setInt("dirLightCount", dirLightCount);
	shader.setInt("spotLightCount", spotLightCount);

	std::string fullname = getFullName();

	shader.set4Float(fullname + ".ambient", ambient);
	shader.set4Float(fullname + ".diffuse", diffuse);
	shader.set4Float(fullname + ".specular", specular);
}

int Light::getIndex()
{
	std::vector<Light*>* currentLightList;

	switch (lightType)
	{
	case LightType::PointLight:
		currentLightList = &pointLightList;
		break;
	case LightType::DirLight:
		currentLightList = &dirLightList;
		break;
	case LightType::SpotLight:
		currentLightList = &spotLightList;
		break;
	default:
		return -1;
	}

	for (int i = 0; i < currentLightList->size(); i++)
		if ((*currentLightList)[i] == this)
			return i;

	return -1;
}

std::string Light::getTypeName()
{
	std::string result;

	switch (lightType)
	{
	case LightType::PointLight:
		result = "pointLight";
		break;
	case LightType::DirLight:
		result = "dirLight";
		break;
	case LightType::SpotLight:
		result = "spotLight";
		break;
	default:
		result = "";
		break;
	}

	return result;
}

void PointLight::Render(Shader shader)
{
	std::string fullname = getFullName();

	shader.Activate();

	shader.set3Float(fullname + ".position", position);

	shader.setFloat(fullname + ".k0", k0);
	shader.setFloat(fullname + ".k1", k1);
	shader.setFloat(fullname + ".k2", k2);

	Light::Render(shader);
}

void DirLight::Render(Shader shader)
{
	std::string fullname = getFullName();

	shader.Activate();

	shader.set3Float(fullname + ".direction", direction);

	Light::Render(shader);
}

void SpotLight::Render(Shader shader)
{
	std::string fullname = getFullName();

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

	Light::Render(shader);
}