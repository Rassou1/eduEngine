#include "LinearVelocityComponent.h"

LinearVelocityComponent::LinearVelocityComponent()
{
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	maxVelocity = glm::vec3(10.0f, 10.0f, 10.0f);
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

}

void LinearVelocityComponent::Accelerate()
{
	velocity += acceleration;
}

void LinearVelocityComponent::ApplyGravity()
{
	velocity.y -= gravity;
}

void LinearVelocityComponent::SetAcceleration(float x, float y, float z)
{
	acceleration.x = x;
	acceleration.y = y;
	acceleration.z = z;
}

void LinearVelocityComponent::Decelerate(float deceleration)
{
	acceleration.x -= deceleration;
	acceleration.y -= deceleration;
	acceleration.z -= deceleration;
}

void LinearVelocityComponent::SetVelocity(float x, float y, float z)
{
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

glm::vec3 LinearVelocityComponent::GetVelocity()
{
	return velocity;
}

void LinearVelocityComponent::Update()
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
