#pragma once
#include <entt/entt.hpp>
#include "LinearVelocityComponent.hpp"
#include "InputManager.hpp"
#include <memory>

	class PlayerControllerComponent {

		
	public:
		PlayerControllerComponent() {};
		bool isMovingForward = false;
		bool isMovingBackward = false;
		bool isMovingLeft = false;
		bool isMovingRight = false;


	};

