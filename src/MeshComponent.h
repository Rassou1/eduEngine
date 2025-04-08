#pragma once
#include <memory>
#include "RenderableMesh.hpp"

namespace eeng {
	
	class MeshComponent
	{
		MeshComponent(){};

	public:
		MeshComponent(std::shared_ptr<RenderableMesh> mesh)
		{
			this->mesh = mesh;
		}
		std::shared_ptr<RenderableMesh> mesh;
	};
}
