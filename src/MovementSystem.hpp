#pragma once
#include "entt/entt.hpp"
#include "LinearVelocityComponent.hpp"
#include "TransformComponent.hpp"
#include <memory>

void MovementSystem(std::shared_ptr<entt::registry> registry, float deltaTime) {

	auto view = registry->view<TransformComponent, LinearVelocityComponent>();

	for (auto entity : view) {
		auto& transform = view.get<TransformComponent>(entity);
		auto& linearVelocity = view.get<LinearVelocityComponent>(entity);

		//transform.Translate(linearVelocity.GetVelocity());

		transform.position += linearVelocity.GetVelocity() * deltaTime;
		//std::cout << "position: " << transform.position.x << transform.position.y << transform.position.z << std::endl;
		//std::cout << "velocity: " << linearVelocity.GetVelocity().x << linearVelocity.GetVelocity().y << linearVelocity.GetVelocity().z << std::endl;
		
		transform.UpdateTransform();
	}

};