#pragma once
#pragma once
#include <glm/glm.hpp>


	class TransformComponent
	{
	public:
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation;

		glm::mat4 transform;

		TransformComponent(float x, float y, float z)
		{
			position.x = x;
			position.y = y;
			position.z = z;
			scale.x = 0.03f;
			scale.y = 0.03f;
			scale.z = 0.03f;

			rotation.y = 0.0f;
			rotation.z = 0.0f;

			UpdateTransform();
		}

		TransformComponent(glm::mat4 input)
		{
			transform = input;

			UpdateTransform();
		}

		TransformComponent(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
		{
			this->position = glm::vec4(position.x, position.y, position.z, 1.0f);
			this->scale = scale;
			this->rotation = rotation;

			UpdateTransform();
		}

		TransformComponent()
		{
			position.x = 0.0f;
			position.y = 0.0f;
			position.z = 0.0f;
			scale.x = 0.03f;
			scale.y = 0.03f;
			scale.z = 0.03f;

			rotation.y = 0.0f;
			rotation.z = 0.0f;
			UpdateTransform();
		}

		glm::mat4 GetTransform() const
		{
			return transform;
		}

		void UpdateTransform()
		{
			transform[0][0] = scale.x * cos(rotation.y) * cos(rotation.z);	transform[1][0] = -scale.y * cos(rotation.y) * sin(rotation.z);	transform[2][0] = scale.z * sin(rotation.y);	transform[3][0] = position.x;
			transform[0][1] = scale.x * sin(rotation.z);					transform[1][1] = scale.y * cos(rotation.z);					transform[2][1] = 0.0f;							transform[3][1] = position.y;
			transform[0][2] = -scale.x * sin(rotation.y) * cos(rotation.z);	transform[1][2] = scale.y * sin(rotation.y) * sin(rotation.z);	transform[2][2] = scale.z * cos(rotation.y);	transform[3][2] = position.z;
			transform[0][3] = 0.0f;											transform[1][3] = 0.0f;											transform[2][3] = 0.0f;							transform[3][3] = 1.0f;
		}

		void Scale(float x, float y, float z)
		{
			scale.x *= x;
			scale.y *= y;
			scale.z *= z;
		}

		void SetScale(float x, float y, float z)
		{
			scale.x = x;
			scale.y = y;
			scale.z = z;
		}

		void Rotate(float rotZ, float rotY)
		{
			rotation.y += rotY;
			rotation.z += rotZ;
		}

		void Translate(float x, float y, float z)
		{
			position.x += x;
			position.y += y;
			position.z += z;
		}

		void Translate(glm::vec3 translationVector)
		{
			position.x += translationVector.x;
			position.y += translationVector.y;
			position.z += translationVector.z;
		}

		void TranslateX(float x)
		{
			position.x += x;
		}

		void TranslateY(float y)
		{
			position.y += y;
		}

		void TranslateZ(float z)
		{
			position.z += z;
		}

		~TransformComponent()
		{
		}

	};



