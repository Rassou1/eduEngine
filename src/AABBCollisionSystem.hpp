//#pragma once
//#include "entt/entt.hpp"
//#include "ColliderComponent.hpp"
//#include "TransformComponent.hpp"
//#include "Log.hpp"
//
//class AABBCollisionSystem
//{
//public:
//	
//	void CheckAABBCollision(entt::registry& registry) 
//	{
//		auto view = registry.view<TransformComponent, ColliderComponent>();
//
//		for (auto entity : view) {
//			auto& transform = view.get<TransformComponent>(entity);
//			auto& collider = view.get<ColliderComponent>(entity);
//
//			collider.aabb.center = transform.position;
//			collider.aabb.halfWidths[0] = transform.scale.x * 0.5f;
//			collider.aabb.halfWidths[1] = transform.scale.y * 0.5f;
//			collider.aabb.halfWidths[2] = transform.scale.z * 0.5f;
//
//			collider.aabb.isColliding = false;
//		}
//
//		for (auto entity : view) {
//			auto& collider = view.get<ColliderComponent>(entity);
//			for (auto otherEntity : view) {
//				if (entity == otherEntity) continue;
//
//				auto& otherCollider = view.get<ColliderComponent>(otherEntity);
//
//				if (CheckAABBDistance(collider.aabb.center, collider.aabb.halfWidths, otherCollider.aabb.center, otherCollider.aabb.halfWidths)) {
//					collider.aabb.isColliding = true;
//					otherCollider.aabb.isColliding = true;
//
//					eeng::Log("AABB collision detected between %d and %d", int(entity), int(otherEntity));
//				}
//			}
//		}
//	}
//
//	bool CheckAABBDistance(const glm::vec3& center, const float halfWidths[3], const glm::vec3& otherCenter, const float otherHalfWidths[3])
//	{
//		glm::vec3 centerToCenterDistance = glm::abs(center - otherCenter);
//
//		glm::vec3 combinedHalfWidths = { 0,0,0 };
//		combinedHalfWidths.x = halfWidths[0] + otherHalfWidths[0];
//		combinedHalfWidths.y = halfWidths[1] + otherHalfWidths[1];
//		combinedHalfWidths.z = halfWidths[2] + otherHalfWidths[2];
//
//		return (centerToCenterDistance.x <= combinedHalfWidths.x && centerToCenterDistance.y <= combinedHalfWidths.y && centerToCenterDistance.z <= combinedHalfWidths.z);
//	}
//
//	void Update(entt::registry& registry)
//	{
//		CheckAABBCollision(registry);
//	}
//
//
//};
