#include "RigidBody.h"
#include "../engine/Engine.h"

void RigidBody::Update(float deltaTime)
{
	Object::Update(deltaTime);

	position += velocity * deltaTime + 0.5f * acceleration * (deltaTime * deltaTime);
	velocity += acceleration * deltaTime;
}

void RigidBody::ApplyForce(glm::vec3 force)
{
	acceleration += force / mass;
}

void RigidBody::ApplyForce(glm::vec3 direction, float magnitude)
{
	ApplyForce(direction * magnitude);
}

void RigidBody::ApplyAcceleration(glm::vec3 _acceleration)
{
	acceleration += _acceleration;
}

void RigidBody::ApplyAcceleration(glm::vec3 direction, float magnitude)
{
	ApplyAcceleration(direction * magnitude);
}

void RigidBody::ApplyImpulse(glm::vec3 force)
{
	velocity += force / mass * Engine::GetDeltaTime();
}

void RigidBody::ApplyImpulse(glm::vec3 direction, float magnitude)
{
	ApplyImpulse(direction * magnitude);
}

void RigidBody::TransferEnergy(float joules)
{
	if (joules == 0) return;

	// Formula: KE = 1/2 * m * v^2
	float deltaV = sqrt(2 * abs(joules) / mass);

	velocity += joules > 0 ? deltaV : -deltaV;
}
