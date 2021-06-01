#pragma once

#include <glm/glm.hpp>

#include "../engine/Object.h"

class RigidBody : public Object
{
public:
	float mass;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	RigidBody(float mass = 1.f, glm::vec3 position = glm::vec3(0.f),
		glm::vec3 velocity = glm::vec3(0.f), glm::vec3 acceleration = glm::vec3(0.f)
	) : mass(mass), position(position), velocity(velocity), acceleration(acceleration) { }

	virtual void Update(float deltaTime) override;

	void ApplyForce(glm::vec3 force);
	void ApplyForce(glm::vec3 direction, float magnitude);

	void ApplyAcceleration(glm::vec3 _acceleration);
	void ApplyAcceleration(glm::vec3 direction, float magnitude);

	void ApplyImpulse(glm::vec3 force);
	void ApplyImpulse(glm::vec3 direction, float magnitude);

	void TransferEnergy(float joules);
};