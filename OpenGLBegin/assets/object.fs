#version 330 core
out vec4 FragColor;

#define MAX_LIGHT_COUNT 25
#define MAX_MAT_COUNT 30

struct Material
{
	vec4 diffuse;
	vec4 specular;
	vec4 emission;

	float shininess;
};
uniform Material material;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

struct PointLight
{
	vec3 position;

	float k0;
	float k1;
	float k2;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
uniform PointLight pointLight[MAX_LIGHT_COUNT];
uniform int pointLightCount;

struct DirLight
{
	vec3 direction;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
uniform DirLight dirLight[MAX_LIGHT_COUNT];
uniform int dirLightCount;

struct SpotLight
{
	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;

	float k0;
	float k1;
	float k2;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
uniform SpotLight spotLight[MAX_LIGHT_COUNT];
uniform int spotLightCount;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 viewPos;

uniform bool noTex;

vec4 calcPointLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap);
vec4 calcDirLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap);
vec4 calcSpotLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap);
vec3 calcEmissionLight(vec3 specMap, vec3 emissionMap);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	// Change diffuse0 and specular0 when code is fixed
	vec4 diffMap;
	vec4 specMap;
	//vec3 emissionMap = isMaterial ? material.emission : vec3(texture(textureMaterial.emission, TexCoord));

	if(noTex)
	{
		diffMap = material.diffuse;
		specMap = material.specular;
	}
	else
	{
		diffMap = texture(diffuse0, TexCoord);
		specMap = texture(specular0, TexCoord);
	}

	vec4 colorResult = vec4(0.f);

	// Point lights
	for(int i = 0; i < pointLightCount; i++)
		colorResult += calcPointLight(i, norm, viewDir, diffMap, specMap);

	// Dir lights
	for(int i = 0; i < dirLightCount; i++)
		colorResult += calcDirLight(i, norm, viewDir, diffMap, specMap);

	for(int i = 0; i < spotLightCount; i++)
		colorResult += calcSpotLight(i, norm, viewDir, diffMap, specMap);

	//colorResult += isMaterial ? vec3(0.f) : calcEmissionLight(specMap, emissionMap);
	
	FragColor = colorResult;
}

vec4 calcPointLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap)
{
	// Ambient
	vec4 ambient = pointLight[idx].ambient * diffMap;

	// Diffuse
	vec3 lightDir = normalize(pointLight[idx].position - FragPos);
	float diff = max(dot(norm, lightDir), 0.f);
	vec4 diffuse = pointLight[idx].diffuse * (diff * diffMap);

	// Specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess * 128);
	vec4 specular = pointLight[idx].specular * (spec * specMap);

	float dist = length(pointLight[idx].position - FragPos);
	float attenuation = 1.f / (pointLight[idx].k0 + pointLight[idx].k1 * dist + pointLight[idx].k2 * (dist * dist));

	return vec4(ambient + diffuse + specular) * attenuation;
}

vec4 calcDirLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap)
{
	// Ambient
	vec4 ambient = dirLight[idx].ambient * diffMap;

	// Diffuse
	vec3 lightDir = normalize(-dirLight[idx].direction);
	float diff = max(dot(norm, lightDir), 0.f);
	vec4 diffuse = dirLight[idx].diffuse * (diff * diffMap);

	// Specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess * 128);
	vec4 specular = dirLight[idx].specular * (spec * specMap);

	return vec4(ambient + diffuse + specular);
}

vec4 calcSpotLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap)
{	
	vec3 lightDir = normalize(spotLight[idx].position - FragPos);
	float theta = dot(lightDir, normalize(-spotLight[idx].direction));

	// Ambient
	vec4 ambient = spotLight[idx].ambient * diffMap;

	if(theta > spotLight[idx].outerCutOff)
	{
		// Diffuse
		float diff = max(dot(norm, lightDir), 0.f);
		vec4 diffuse = spotLight[idx].diffuse * (diff * diffMap);

		// Specular
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess * 128);
		vec4 specular = spotLight[idx].specular * (spec * specMap);

		float intensity = (theta - spotLight[idx].outerCutOff) / (spotLight[idx].cutOff - spotLight[idx].outerCutOff);
		intensity = clamp(intensity, 0.f, 1.f);
		diffuse *= intensity;
		specular *= intensity;

		float dist = length(spotLight[idx].position - FragPos);
		float attenuation = 1.f / (spotLight[idx].k0 + spotLight[idx].k1 * dist + spotLight[idx].k2 * (dist * dist));

		return vec4(ambient + diffuse + specular) * attenuation;
	}
	else
		return ambient;
}

vec3 calcEmissionLight(vec3 specMap, vec3 emissionMap)
{
	vec3 show = step(vec3(1.f), vec3(1.f) - specMap);
	return emissionMap * show;
}