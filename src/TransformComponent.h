#pragma once
#include <glm/glm.hpp>
namespace eeng 
{
	class TransformComponent
	{
	public:
		TransformComponent(float x, float y, float z);
		TransformComponent();

		glm::vec4 position;
		glm::vec3 scale;
		glm::vec3 rotation;

		glm::mat4x4 transform;

		glm::mat4 GetTransform() const;

		

		void Scale(float x, float y, float z);
		void SetScale(float x, float y, float z);

		void Rotate(float rotZ, float rotY);
		
		void Translate(float x, float y, float z);
		void TranslateX(float x);
		void TranslateY(float y);
		void TranslateZ(float z);
		

		void UpdateTransform();

		~TransformComponent();
	};
}


