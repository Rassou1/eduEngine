#pragma once
#include <entt/entt.hpp>
#include "TransformComponent.hpp"
#include "MeshComponent.hpp"
#include "ForwardRenderer.hpp"
#include "glm/glm.hpp"
#include "shapeRenderer.hpp"
#include "AnimationComponent.hpp"
#include "imgui.h"


namespace eeng {

	void RenderSystem(eeng::ForwardRendererPtr forwardRenderer, std::shared_ptr<entt::registry> registry, ShapeRendererPtr shapeRenderer)
		//ADD ANIMATION ASK HECTOR?
	{
		auto view = registry->view<TransformComponent, MeshComponent>();
		for (auto entity : view) {
			auto& transform = view.get<TransformComponent>(entity);
			auto& mesh = view.get<MeshComponent>(entity);

			//RenderBoneAxles(mesh, transform, shapeRenderer);

			//If statement below not needed since not using weak ptr, only a shared ptr
			//if (auto meshPtr = mesh.mesh.lock())
			forwardRenderer->renderMesh(mesh.mesh, transform.transform);
		}
	}

	void RenderBoneAxles(MeshComponent& mesh, TransformComponent& transform, ShapeRendererPtr shapeRenderer) {
		bool drawSkeleton = true;
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
	void AnimateGUI(AnimationComponent animate, MeshComponent mesh, Game::Matrices matrices)
	{
		if (mesh.mesh)
		{
			// Combo (drop-down) for animation clip
			int curAnimIndex = animate.animationIndex;
			std::string label = (curAnimIndex == -1 ? "Bind pose" : mesh.mesh->getAnimationName(curAnimIndex));
			if (ImGui::BeginCombo("Character animation##animclip", label.c_str()))
			{
				// Bind pose item
				const bool isSelected = (curAnimIndex == -1);
				if (ImGui::Selectable("Bind pose", isSelected))
					curAnimIndex = -1;
				if (isSelected)
					ImGui::SetItemDefaultFocus();

				// Clip items
				for (int i = 0; i < mesh.mesh->getNbrAnimations(); i++)
				{
					const bool isSelected = (curAnimIndex == i);
					const auto label = mesh.mesh->getAnimationName(i) + "##" + std::to_string(i);
					if (ImGui::Selectable(label.c_str(), isSelected))
						curAnimIndex = i;
					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
				animate.animationIndex = curAnimIndex;
			}

			// In-world position label
			const auto VP_P_V = matrices.VP * matrices.P * matrices.V;
			auto world_pos = glm::vec3(0, 0, 0);
			glm::ivec2 window_coords;
			if (glm_aux::window_coords_from_world_pos(world_pos, VP_P_V, window_coords))
			{
				ImGui::SetNextWindowPos(
					ImVec2{ float(window_coords.x), float(matrices.windowSize.y - window_coords.y) },
					ImGuiCond_Always,
					ImVec2{ 0.0f, 0.0f });
				ImGui::PushStyleColor(ImGuiCol_WindowBg, 0x80000000);
				ImGui::PushStyleColor(ImGuiCol_Text, 0xffffffff);

				ImGuiWindowFlags flags =
					ImGuiWindowFlags_NoDecoration |
					ImGuiWindowFlags_NoInputs |
					// ImGuiWindowFlags_NoBackground |
					ImGuiWindowFlags_AlwaysAutoResize;

				if (ImGui::Begin("window_name", nullptr, flags))
				{
					ImGui::Text("In-world GUI element");
					ImGui::Text("Window pos (%i, %i)", window_coords.x, window_coords.x);
					ImGui::Text("World pos (%1.1f, %1.1f, %1.1f)", world_pos.x, world_pos.y, world_pos.z);
					ImGui::End();
				}
				ImGui::PopStyleColor(2);
			}
		}

		ImGui::SliderFloat("Animation speed", &animate.animationSpeed, 0.1f, 5.0f);
	}

	void RenderSystem(eeng::ForwardRendererPtr forwardRenderer, std::shared_ptr<entt::registry> registry, ShapeRendererPtr shapeRenderer, float time, Game::Matrices matrices)
	{
		auto view = registry->view<TransformComponent, MeshComponent, AnimationComponent>();

		for (auto entity : view) {
			auto& transform = view.get<TransformComponent>(entity);
			auto& mesh = view.get<MeshComponent>(entity);
			auto& animation = view.get<AnimationComponent>(entity);

			RenderBoneAxles(mesh, transform, shapeRenderer);
			AnimateGUI(animation, mesh, matrices);

			mesh.mesh->animate(animation.animationIndex, (time * animation.animationSpeed));
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




