#pragma once
#include <memory>
#include "RenderableMesh.hpp"
#include "InputManager.hpp"


	class MeshComponent
	{
	public:
		MeshComponent() {};

		MeshComponent(std::shared_ptr<eeng::RenderableMesh> mesh)
		{
			this->mesh = mesh;
		}

		MeshComponent(std::shared_ptr<eeng::RenderableMesh> mesh, float axleLength)
		{
			this->mesh = mesh;
			this->axleLength = axleLength;
		}

		MeshComponent(std::shared_ptr<eeng::RenderableMesh> mesh, float axleLength, int animationIndex, bool blend)
		{
			this->mesh = mesh;
			this->axleLength = axleLength;
			this->animationIndex = animationIndex;
			this->blend = blend;
		}

		void Update(int animationIndex)
		{
			this->animationIndex = animationIndex;
		}

		bool blend = false;
		std::shared_ptr<eeng::RenderableMesh> mesh;
		float axleLength = 1;
		int animationIndex = 0;
	};



