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
		std::shared_ptr<eeng::RenderableMesh> mesh;
	};

