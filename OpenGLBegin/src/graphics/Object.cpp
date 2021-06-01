#include "Object.h"

void Object::BeginPlay() { }

void Object::Update(float deltaTime) { }

void Object::SpawnObject(Object* object)
{
	object->BeginPlay();

	objectList.push_back(object);
}

void Object::DestroyObject(Object* object)
{

}