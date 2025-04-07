#pragma once
#include <glm/glm.hpp>

class LinearVelocityComponent
{
	glm::vec3 velocity;
	glm::vec3 maxVelocity;
	glm::vec3 acceleration;
	float gravity = 0.5;

public:
	LinearVelocityComponent();

	void Accelerate();
	void ApplyGravity();
	void SetAcceleration(float x, float y, float z);
	void Decelerate(float deceleration);

	void SetVelocity(float x, float y, float z);
	glm::vec3 GetVelocity();

	void Update();
};

