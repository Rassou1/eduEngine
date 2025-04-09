#pragma once
#include "ForwardRenderer.hpp"
#include "TransformComponent.hpp"
#include "MeshComponent.hpp"
#include <entt/entt.hpp>


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

	void RenderSystem(eeng::ForwardRendererPtr forwardRenderer, std::shared_ptr<eeng::RenderableMesh> mesh, glm::mat4 transform)
	{
		forwardRenderer->renderMesh(mesh, transform);
	}

