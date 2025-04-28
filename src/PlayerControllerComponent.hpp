#pragma once
#include <entt/entt.hpp>
#include <memory>

	class PlayerControllerComponent {

		
	public:
		PlayerControllerComponent() {};
		bool isMovingForward = false;
		bool isMovingBackward = false;
		bool isMovingLeft = false;
		bool isMovingRight = false;


	};

