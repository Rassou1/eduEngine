#pragma once
#include <entt/entt.hpp>
#include "TransformComponent.hpp"
#include "MeshComponent.hpp"
#include "ForwardRenderer.hpp"


namespace eeng {

	void RenderSystem(eeng::ForwardRendererPtr forwardRenderer, std::shared_ptr<entt::registry> registry)
	{
		auto view = registry->view<TransformComponent, MeshComponent>();
		for (auto entity : view) {
			auto& transform = view.get<TransformComponent>(entity);
			auto& mesh = view.get<MeshComponent>(entity);


			//If statement below not needed since not using weak ptr, only a shared ptr
			//if (auto meshPtr = mesh.mesh.lock())
			forwardRenderer->renderMesh(mesh.mesh, transform.transform);
		}
	}

	void RenderSystem(eeng::ForwardRendererPtr forwardRenderer, std::shared_ptr<RenderableMesh> mesh, glm::mat4 transform)
	{
		forwardRenderer->renderMesh(mesh, transform);
	}
}

	/*class RenderSystem
	{
		RenderSystem() {};
		eeng::ForwardRenderer* forwardRendererPtr;
		entt::registry registry;
		std::shared_ptr<entt::registry> registryPtr;
	public:

		RenderSystem(eeng::ForwardRenderer* forwardRendererPtr, std::shared_ptr<entt::registry> registry)
			: forwardRendererPtr(forwardRendererPtr), registry(registry)
		{
			this->forwardRendererPtr = forwardRendererPtr;
			registry = registry;
		}

		void Render()
		{
			auto view = registry.view<TransformComponent, MeshComponent>();
			for (auto entity : view) {
				auto& transform = view.get<TransformComponent>(entity);
				auto& mesh = view.get<MeshComponent>(entity);

			}
		}
	};*/




