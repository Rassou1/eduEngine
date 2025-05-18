#pragma once
#include <entt/entt.hpp>
#include "TransformComponent.hpp"
#include "MeshComponent.hpp"
#include "ForwardRenderer.hpp"
#include "glm/glm.hpp"
#include "shapeRenderer.hpp"
#include "imgui.h"
#include "FSMComponent.hpp"



class RenderSystem {

public:

	//REFACTOR: Dupicate code removal

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

	void Render(eeng::ForwardRendererPtr forwardRenderer, std::shared_ptr<entt::registry> registry, ShapeRendererPtr shapeRenderer, float time)
	{
		auto view = registry->view<MeshComponent, FSMComponent>();
		for (auto entity : view) {
			auto& mesh = view.get<MeshComponent>(entity);
			auto& FSM = view.get<FSMComponent>(entity);

			FSM.ApplyAnimation(mesh, time);
		}

		auto view2 = registry->view<TransformComponent, MeshComponent>();
		for (auto entity : view2) {
			auto& transform = view2.get<TransformComponent>(entity);
			auto& mesh = view2.get<MeshComponent>(entity);

			RenderBoneAxles(mesh, transform, shapeRenderer);

			if (!mesh.blend) 
			{
				mesh.mesh->animate(mesh.animationIndex, time * 1.0f);
			}
			forwardRenderer->renderMesh(mesh.mesh, transform.transform);
		}
	}

	void ToggleBones(InputManagerPtr input)
	{
		using Key = eeng::InputManager::Key;
		if (input->IsKeyPressed(Key::B)) {
			showBones = !showBones;
		}
	}

	void RenderUI(std::shared_ptr<entt::registry> registry)
	{
		ImGui::Begin("Animation State Debug");

		auto view = registry->view<FSMComponent>();
		for (auto entity : view) {
			auto& fsm = view.get<FSMComponent>(entity);

			ImGui::Text("Entity %d", (int)entity);

			if (fsm.currentState == FSMComponent::State::Idle) {
				ImGui::TextColored(ImVec4(0, 1, 0, 1), "Current State: Idle");
			}
			else if (fsm.currentState == FSMComponent::State::Moving) {
				ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), "Current State: Walking");
			}
			else if(fsm.currentState == FSMComponent::State::TransitionToIdle || fsm.currentState == FSMComponent::State::TransitionToMoving){
				ImGui::TextColored(ImVec4(1, 0, 0, 1), "Current State: Transitioning");
			}

			ImGui::Separator();
		}

		if (ImGui::Button(showBones ? "Hide Bones" : "Show Bones")) {
			showBones = !showBones;
		}

		ImGui::End();
	}

	void Update(std::shared_ptr<entt::registry> registry, float deltaTime)
	{
		auto view = registry->view<LinearVelocityComponent, FSMComponent>();
		for (auto entity : view) {
			auto& velocity = view.get<LinearVelocityComponent>(entity);
			auto& FSM = view.get<FSMComponent>(entity);

			FSM.Update(deltaTime, velocity.GetVelocity());
		}
	}
};