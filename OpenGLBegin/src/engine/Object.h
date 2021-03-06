#pragma once
#include <vector>
#include "../graphics/Shader.h"

class Object
{
public:
	virtual void BeginPlay();

	virtual void Update(float deltaTime);

	static void RenderAllObjects(Shader& shader);

	static void DestroyAllObjects();

	virtual void SpawnObject();

	static void SpawnObject(Object* object) { object->SpawnObject(); }

	virtual void DestroyObject();

	static void DestroyObject(Object* object) { object->DestroyObject(); }

protected:
	virtual void Render(Shader& shader);

	bool UseUpdate = true;

private:
	static std::vector<Object*> objectList;
};