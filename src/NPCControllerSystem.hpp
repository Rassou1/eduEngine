#pragma once
#include "NPCControllerComponent.hpp"
#include "MovementSystem.hpp"

void NPCControllerSystem(std::shared_ptr<entt::registry> registry) {

	auto view = registry->view<NPCControllerComponent, LinearVelocityComponent, TransformComponent>();

	for (auto entity : view) {

		auto& npcController = view.get<NPCControllerComponent>(entity);
		auto& linearVelocity = view.get<LinearVelocityComponent>(entity);
		auto& transform = view.get<TransformComponent>(entity);
		
		float distance = glm::distance(transform.position, npcController.nextWaypoint);
		
		if (distance > 0.1) {
			glm::vec3 direction = glm::normalize(npcController.nextWaypoint - transform.position);
			linearVelocity.SetVelocity(direction * 10.0f); 
		}
		else {
			npcController.UpdateWaypoint();
		}
		
	}
}