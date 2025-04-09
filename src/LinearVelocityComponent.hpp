#pragma once
#include <glm/glm.hpp>

class LinearVelocityComponent
{
	glm::vec3 velocity;
	glm::vec3 maxVelocity;
	glm::vec3 acceleration;
	float gravity = 0.5;

public:
	LinearVelocityComponent()
	{
		velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		maxVelocity = glm::vec3(10.0f, 10.0f, 10.0f);
		acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	void Accelerate()
	{
		velocity += acceleration;
	}

	void ApplyGravity()
	{
		velocity.y -= gravity;
	}

	void SetAcceleration(float x, float y, float z)
	{
		acceleration.x = x;
		acceleration.y = y;
		acceleration.z = z;
	}

	void Decelerate(float deceleration)
	{
		acceleration.x -= deceleration;
		acceleration.y -= deceleration;
		acceleration.z -= deceleration;
	}

	void SetVelocity(float x, float y, float z)
	{
		velocity.x = x;
		velocity.y = y;
		velocity.z = z;
	}

	void SetVelocity(glm::vec3 inputVector)
	{
		velocity.x = inputVector.x;
		velocity.y = inputVector.y;
		velocity.z = inputVector.z;
	}

	void SetXVelocity(float x)
	{
		velocity.x = x;
	}

	void SetYVelocity(float y)
	{
		velocity.y = y;
	}

	void SetZVelocity(float z)
	{
		velocity.z = z;
	}

	glm::vec3 GetVelocity()
	{
		return velocity;
	}

	void Update()
	{
		Accelerate();
		ApplyGravity();

		if (velocity.x > maxVelocity.x)
		{
			velocity.x = maxVelocity.x;
		}
		if (velocity.y > maxVelocity.y)
		{
			velocity.y = maxVelocity.y;
		}
		if (velocity.z > maxVelocity.z)
		{
			velocity.z = maxVelocity.z;
		}
	}

};

#pragma once
