#include "TransformComponent.h"

eeng::TransformComponent::TransformComponent(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;

	rotation.y = 0.0f;
	rotation.z = 0.0f;

	UpdateTransform();
}

eeng::TransformComponent::TransformComponent()
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;

	rotation.y = 0.0f;
	rotation.z = 0.0f;
	UpdateTransform();
}

glm::mat4 eeng::TransformComponent::GetTransform() const
{
	return transform;
}

void eeng::TransformComponent::UpdateTransform() 
{
	transform[0][0] = scale.x * cos(rotation.y) * cos(rotation.z);	transform[1][0] = -scale.y * cos(rotation.y) * sin(rotation.z);	transform[2][0] = scale.z * sin(rotation.y);	transform[3][0] = position.x;
	transform[0][1] = scale.x * sin(rotation.z);					transform[1][1] = scale.y * cos(rotation.z);					transform[2][1] = 0.0f;							transform[3][1] = position.y;
	transform[0][2] = -scale.x * sin(rotation.y) * cos(rotation.z);	transform[1][2] = scale.y * sin(rotation.y) * sin(rotation.z);	transform[2][2] = scale.z * cos(rotation.y);	transform[3][2] = position.z;
	transform[0][3] = 0.0f;											transform[1][3] = 0.0f;											transform[2][3] = 0.0f;							transform[3][3] = 1.0f;
}

void eeng::TransformComponent::Scale(float x, float y, float z)
{
	scale.x *= x;
	scale.y *= y;
	scale.z *= z;
}

void eeng::TransformComponent::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void eeng::TransformComponent::Rotate(float rotZ, float rotY)
{
	rotation.y += rotY;
	rotation.z += rotZ;
}

void eeng::TransformComponent::Translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void eeng::TransformComponent::TranslateX(float x)
{
	position.x += x;
}

void eeng::TransformComponent::TranslateY(float y)
{
	position.y += y;
}

void eeng::TransformComponent::TranslateZ(float z)
{
	position.z += z;
}

eeng::TransformComponent::~TransformComponent()
{
	delete this;
}
