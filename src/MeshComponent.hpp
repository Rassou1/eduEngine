#pragma once
#include <memory>
#include "RenderableMesh.hpp"


	class MeshComponent
	{
		MeshComponent(){};

	public:
		MeshComponent(std::shared_ptr<eeng::RenderableMesh> mesh)
		{
			this->mesh = mesh;
		}

		MeshComponent(std::shared_ptr<eeng::RenderableMesh> mesh, float axleLength)
		{
			this->mesh = mesh;
			this->axleLength = axleLength;
		}

		std::shared_ptr<eeng::RenderableMesh> mesh;
		float axleLength = 1;
	};



