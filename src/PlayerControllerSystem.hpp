#pragma once
#include "PlayerControllerComponent.hpp"
#include "MovementSystem.hpp"

void PlayerControllerSystem(std::shared_ptr<entt::registry> registry, InputManagerPtr input) {

	auto view = registry->view<PlayerControllerComponent, LinearVelocityComponent>();

	for (auto entity : view) {
		
		auto& playerController = view.get<PlayerControllerComponent>(entity);
		auto& linearVelocity = view.get<LinearVelocityComponent>(entity);

		using Key = eeng::InputManager::Key;
		playerController.isMovingForward = input->IsKeyPressed(Key::W);
		playerController.isMovingLeft = input->IsKeyPressed(Key::A);
		playerController.isMovingBackward = input->IsKeyPressed(Key::S);
		playerController.isMovingRight = input->IsKeyPressed(Key::D);


		if (playerController.isMovingForward) {
			linearVelocity.SetZVelocity(-5);
		}
		if (playerController.isMovingBackward) {
			linearVelocity.SetZVelocity(5);
		}
		if (playerController.isMovingLeft) {
			linearVelocity.SetXVelocity(-5);
		}
		if (playerController.isMovingRight) {
			linearVelocity.SetXVelocity(5);
		}
		 
		if (!playerController.isMovingForward && !playerController.isMovingBackward && !playerController.isMovingLeft && !playerController.isMovingRight) {
			linearVelocity.SetVelocity(glm::vec3(0, 0, 0));
		}
	}
}