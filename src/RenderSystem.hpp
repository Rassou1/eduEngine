#pragma once
#include <entt/entt.hpp>
#include "TransformComponent.hpp"
#include "MeshComponent.hpp"
#include "ForwardRenderer.hpp"
#include "glm/glm.hpp"
#include "shapeRenderer.hpp"
#include "imgui.h"



class RenderSystem {

public:

	RenderSystem() {};

	bool showBones = true;

	void RenderBoneAxles(MeshComponent& mesh, TransformComponent& transform, ShapeRendererPtr shapeRenderer) {
		//Add a toggle key.

		if (showBones) {
			for (int i = 0; i < mesh.mesh->boneMatrices.size(); ++i) {
				auto IBinverse = glm::inverse(mesh.mesh->m_bones[i].inversebind_tfm);

				glm::mat4 global = transform.transform * mesh.mesh->boneMatrices[i] * IBinverse;
				glm::vec3 pos = glm::vec3(global[3]);

				glm::vec3 right = glm::vec3(global[0]); // X
				glm::vec3 up = glm::vec3(global[1]); // Y
				glm::vec3 fwd = glm::vec3(global[2]); // Z

				shapeRenderer->push_states(ShapeRendering::Color4u::Red);
				shapeRenderer->push_line(pos, pos + mesh.axleLength * right);

				shapeRenderer->push_states(ShapeRendering::Color4u::Green);
				shapeRenderer->push_line(pos, pos + mesh.axleLength * up);

				shapeRenderer->push_states(ShapeRendering::Color4u::Blue);
				shapeRenderer->push_line(pos, pos + mesh.axleLength * fwd);

				shapeRenderer->pop_states<ShapeRendering::Color4u>();
				shapeRenderer->pop_states<ShapeRendering::Color4u>();
				shapeRenderer->pop_states<ShapeRendering::Color4u>();
			};
		}
	}

	void Render(eeng::ForwardRendererPtr forwardRenderer, std::shared_ptr<entt::registry> registry, ShapeRendererPtr shapeRenderer, float time, int CharacterAnimationIndex)
	{
		auto view = registry->view<TransformComponent, MeshComponent>();
		for (auto entity : view) {
			auto& transform = view.get<TransformComponent>(entity);
			auto& mesh = view.get<MeshComponent>(entity);

			RenderBoneAxles(mesh, transform, shapeRenderer);

			mesh.Update(CharacterAnimationIndex); // Update the animation index if needed

			mesh.mesh->animate(mesh.animationIndex, time * 1.0f); //UNNECESSARILY COMPLICATED MIGHT BE ABLE TO JUST USE THE STUFF IN GAME.CPP ASK CJ


			//If statement below not needed since not using weak ptr, only a shared ptr
			//if (auto meshPtr = mesh.mesh.lock())
			forwardRenderer->renderMesh(mesh.mesh, transform.transform);
		}
	}

	void Render(eeng::ForwardRendererPtr forwardRenderer, std::shared_ptr<entt::registry> registry, ShapeRendererPtr shapeRenderer)
	{
		auto view = registry->view<TransformComponent, MeshComponent>();
		for (auto entity : view) {
			auto& transform = view.get<TransformComponent>(entity);
			auto& mesh = view.get<MeshComponent>(entity);

			RenderBoneAxles(mesh, transform, shapeRenderer);

			//Add a bind (for some god forsaken reason) that turns off the bone axle rendering.

			//If statement below not needed since not using weak ptr, only a shared ptr
			//if (auto meshPtr = mesh.mesh.lock())
			forwardRenderer->renderMesh(mesh.mesh, transform.transform);
		}
	}

	void ToggleBones(InputManagerPtr input)
	{
		using Key = eeng::InputManager::Key;
		showBones = !input->IsKeyPressed(Key::B);
	}

};



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




