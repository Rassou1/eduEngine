#pragma once
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"
#include "PlayerControllerComponent.hpp"
#include "SourceComponent.hpp"
#include <entt/entt.hpp>
#include "InputManager.hpp"
#include <cstdlib>
#include "Log.hpp"
#include "FSMComponent.hpp"
#include "BrushingComponent.hpp"
#include "Tags.hpp"

class InteractionSystem : public SourceComponent 
{
	entt::entity horse = entt::null;
public:
	InteractionSystem()
	{

	};
	void Update(std::shared_ptr<entt::registry> registry, InputManagerPtr input, EventQueue* eventQueue, QuestObserver* questObserver, float deltaTime) 
	{
		using key = eeng::InputManager::Key;

		entt::entity player = GetPlayer(registry);

		if (player == entt::null)
		{
			return;
		}

		HandleHorseInteraction(registry, input, player, eventQueue, questObserver, deltaTime);

		if (input->IsKeyPressed(key::E))
		{
			HandleQuestStart(registry, input, player, eventQueue, questObserver);

			eeng::Log("Current event state is: %d", int(questObserver->GetProgress()));
			HandleBrushInteraction(registry, input, player, eventQueue, questObserver, deltaTime);
		}
	}

	entt::entity GetPlayer(std::shared_ptr<entt::registry> registry)
	{
		auto view = registry->view<TransformComponent, ColliderComponent, PlayerControllerComponent>();

		for (auto entity : view)
		{
			return entity;
		}
		return entt::entity();
	}

	void HandleQuestStart(std::shared_ptr<entt::registry> registry, InputManagerPtr input, entt::entity player, EventQueue* eventQueue, QuestObserver* questObserver)
	{
		using key = eeng::InputManager::Key;

		if (questObserver->GetProgress() != QuestObserver::QuestProgression::NotStarted)
		{
			return;
		}

		auto& playerTransform = registry->get<TransformComponent>(player);
		auto& playerCollider = registry->get<ColliderComponent>(player);
		glm::vec3 playerCenter = playerTransform.position;

		auto targets = registry->view<TransformComponent, ColliderComponent, QuestGiveTag>();
		for (auto npc : targets)
		{
			auto& npcTransform = registry->get<TransformComponent>(npc);
			auto& npcCollider = registry->get<ColliderComponent>(npc);
			glm::vec3 npcCenter = npcTransform.position;

			float distanceSq = glm::dot(playerCenter - npcCenter, playerCenter - npcCenter);
			float radiusSum = playerCollider.sphere.radius + npcCollider.sphere.radius + 100;

			if (distanceSq <= radiusSum * radiusSum)
			{
				eeng::Log("Player has started the Quest!");
				eventQueue->push(Event{EventTypes::EVENT_STARTED_QUEST});
				Notify(EventTypes::EVENT_STARTED_QUEST);
			}

		}
	}

	void HandleBrushInteraction(std::shared_ptr<entt::registry> registry, InputManagerPtr input, entt::entity player, EventQueue* eventQueue, QuestObserver* questObserver, float deltaTime)
	{
		using key = eeng::InputManager::Key;

		if (questObserver->GetProgress() != QuestObserver::QuestProgression::Started)
		{
			return;
		}

		eeng::Log("HandleBrushInteraction");
				eeng::Log("Player equipped the brush.");
				eventQueue->push(Event{ EventTypes::EVENT_BRUSH_FOUND});
				Notify(EventTypes::EVENT_BRUSH_FOUND);
	}

	void HandleHorseInteraction(std::shared_ptr<entt::registry> registry, InputManagerPtr input, entt::entity player, EventQueue* eventQueue, QuestObserver* questObserver, float deltaTime) 
	{
		using key = eeng::InputManager::Key;

		if (questObserver->GetProgress() != QuestObserver::QuestProgression::BrushInInventory)
		{
			return;
		}

		auto& playerTransform = registry->get<TransformComponent>(player);
		auto& playerCollider = registry->get<ColliderComponent>(player);
		auto& playerAnimation = registry->get<FSMComponent>(player);
		glm::vec3 playerCenter = playerTransform.position;

		auto targets = registry->view<TransformComponent, ColliderComponent, BrushingComponent>();
		for (auto horse : targets)
		{
			auto& horseTransform = registry->get<TransformComponent>(horse);
			auto& horseCollider = registry->get<ColliderComponent>(horse);

			// Debug to see if being reached
			eeng::Log("Trying Horse interaction with entity %d", int(horse));

			glm::vec3 horseCenter = horseTransform.position;
			float distanceSq = glm::dot(playerCenter - horseCenter, playerCenter - horseCenter);
			float radiusSum = playerCollider.sphere.radius + horseCollider.sphere.radius;

			if (distanceSq <= radiusSum * radiusSum + 5)
			{
				if (input->IsKeyPressed(key::E))
				{
					eeng::Log("Player is brushing the horse.");
				}
			}

		}
	}

};