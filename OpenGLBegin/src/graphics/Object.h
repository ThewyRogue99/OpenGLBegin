#pragma once
#include <vector>

class Object
{
public:
	virtual void BeginPlay();

	virtual void Update(float deltaTime);

protected:
	static void SpawnObject(Object* object);

	static void DestroyObject(Object* object);

private:
	static std::vector<Object*> objectList;
};