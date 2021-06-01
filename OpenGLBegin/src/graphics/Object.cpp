#include "Object.h"

std::vector<Object*> Object::objectList = { };

void Object::BeginPlay() { }

void Object::Update(float deltaTime) { }

void Object::Render(Shader shader) { }

void Object::RenderAllObjects(Shader shader)
{
	shader.Activate();

	for (Object* object : objectList)
		object->Render(shader);
}

void Object::UpdateAllObjects(float deltaTime)
{
	for (Object* object : objectList)
		if (object->UseUpdate)
			object->Update(deltaTime);
}

void Object::DestroyAllObjects()
{
	int size = objectList.size();

	for (int i = 0; i < size; i++)
		objectList[0]->DestroyObject();
}

void Object::SpawnObject()
{
	BeginPlay();

	objectList.push_back(this);
}

void Object::DestroyObject()
{
	for (int i = 0; i < objectList.size(); i++)
		if (objectList[i] == this)
			objectList.erase(objectList.begin() + i);
}