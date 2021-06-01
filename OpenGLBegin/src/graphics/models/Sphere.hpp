#include "../Model.h"

class Sphere : public Model
{
public:
	Sphere(glm::vec3 position = glm::vec3(0.f), glm::vec3 size = glm::vec3(1.f), glm::vec3 rotation = glm::vec3(0.f))
		: Model(position, size, rotation, true) { }

	void init() { loadModel("assets/models/sphere/scene.gltf"); }
};