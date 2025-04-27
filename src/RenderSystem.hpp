#pragma once
#include <entt/entt.hpp>
#include "TransformComponent.hpp"
#include "MeshComponent.hpp"
#include "ForwardRenderer.hpp"
#include "glm/glm.hpp"
#include "shapeRenderer.hpp"


namespace eeng {

	void RenderSystem(eeng::ForwardRendererPtr forwardRenderer, std::shared_ptr<entt::registry> registry, ShapeRendererPtr shapeRenderer)
		//ADD ANIMATION ASK HECTOR?
	{
		auto view = registry->view<TransformComponent, MeshComponent>();
		for (auto entity : view) {
			auto& transform = view.get<TransformComponent>(entity);
			auto& mesh = view.get<MeshComponent>(entity);

			bool drawSkeleton = true;
			float axisLen = 25.0f;
			//Need to figure out axisLen. at 25 we get normal lengths for the girl, at 1 we get normal lengths for the horse.
			//Add a toggle key.

			if (drawSkeleton) {
				for (int i = 0; i < mesh.mesh->boneMatrices.size(); ++i) {
					auto IBinverse = glm::inverse(mesh.mesh->m_bones[i].inversebind_tfm);
					
					glm::mat4 global = transform.transform * mesh.mesh->boneMatrices[i] * IBinverse;
					glm::vec3 pos = glm::vec3(global[3]);

					glm::vec3 right = glm::vec3(global[0]); // X
					glm::vec3 up = glm::vec3(global[1]); // Y
					glm::vec3 fwd = glm::vec3(global[2]); // Z

					shapeRenderer->push_states(ShapeRendering::Color4u::Red);
					shapeRenderer->push_line(pos, pos + axisLen * right);

					shapeRenderer->push_states(ShapeRendering::Color4u::Green);
					shapeRenderer->push_line(pos, pos + axisLen * up);

					shapeRenderer->push_states(ShapeRendering::Color4u::Blue);
					shapeRenderer->push_line(pos, pos + axisLen * fwd);

					shapeRenderer->pop_states<ShapeRendering::Color4u>();
					shapeRenderer->pop_states<ShapeRendering::Color4u>();
					shapeRenderer->pop_states<ShapeRendering::Color4u>();
				};
			}


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




