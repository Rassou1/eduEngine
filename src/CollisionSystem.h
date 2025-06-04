#pragma once
#include <glm/glm.hpp>
#include "ColliderComponent.hpp"
#include "TransformComponent.hpp"
#include "Log.hpp"
#include <cstdlib>
#include <vector>

struct SimpleContact {
	uint32_t idA;
	uint32_t idB;
	float penetrationDepth;
	glm::vec3 contactPoint;
	glm::vec3 contactNormal;
};

struct SphereNode {
	Sphere* collisionRepresentation = nullptr;
	SphereNode* leftChild = nullptr;
	SphereNode* rightChild = nullptr;
	bool isTrigger;
};

//struct SphereNode
//{
//	entt::entity entity = entt::null;
//	glm::vec3 center;
//	float radius;
//
//	SphereNode* leftChild = nullptr;
//	SphereNode* rightChild = nullptr;
//
//	bool isLeaf() const {
//		return leftChild == nullptr && rightChild == nullptr;
//	}
//};

class SphereCollisionSystem {

	SphereNode* rootNode = nullptr;
	std::vector<Sphere*> spheres; 

public:

	SphereCollisionSystem() {};

#pragma region newCode
	//bool CheckSphereCollision(const glm::vec3& center, float radius, const glm::vec3& otherCenter, float otherRadius) 
	//{
	//	float distanceSquared = glm::dot(otherCenter - center, otherCenter - center);
	//	float radiusSum = radius + otherRadius;
	//	return distanceSquared <= radiusSum * radiusSum;
	//}

	//float CheckSphereDistance(SphereNode* sphere, SphereNode* otherSphere) {
	//	float distanceBetweenCenters = glm::length(sphere->center - otherSphere->center);
	//	return distanceBetweenCenters - (sphere->radius + otherSphere->radius);
	//}

	//void CheckSphereSphere(entt::registry* registry)
	//{
	//	auto view = registry->view<TransformComponent, ColliderComponent>();
	//	for (auto entity : view) {
	//		auto& transform = view.get<TransformComponent>(entity);
	//		auto& collider = view.get<ColliderComponent>(entity);

	//		glm::vec3 center = transform.position + collider.sphere.center;
	//		collider.sphere.isColliding = false;

	//		for (auto otherEntity : view) {
	//			if (entity == otherEntity) continue;

	//			auto& otherTransform = view.get<TransformComponent>(otherEntity);
	//			auto& otherCollider = view.get<ColliderComponent>(otherEntity);

	//			glm::vec3 otherCenter = otherTransform.position + otherCollider.sphere.center;

	//			if (CheckSphereCollision(center, collider.sphere.radius, otherCenter, otherCollider.sphere.radius)) 
	//			{
	//				collider.sphere.isColliding = true;
	//				//eeng::Log("Collision detected between: %d <-> %d", int(entity), int(otherEntity));
	//			}

	//		}
	//	}
	//}

	//void BuildLeafNodes(entt::registry& registry) 
	//{
	//	std::vector<SphereNode*> leafNodes;

	//	auto view = registry.view<TransformComponent, ColliderComponent>();
	//	for (auto entity : view) {
	//		auto& transform = view.get<TransformComponent>(entity);
	//		auto& collider = view.get<ColliderComponent>(entity);

	//		glm::vec3 center = transform.position + collider.sphere.center;
	//		float radius = collider.sphere.radius;

	//		SphereNode* node = new SphereNode{ entity, center, radius };
	//		leafNodes.push_back(node);

	//		collider.sphere.isColliding = false;
	//	}

	//	rootNode = BuildBVHBottomUp(leafNodes, 500.0f);
	//}

	//SphereNode* BuildBVHBottomUp(std::vector<SphereNode*> sphereNodes, float maxInitialDistance) 
	//{
	//	while (sphereNodes.size() > 1)
	//	{
	//		std::vector<SphereNode*> openList;

	//		while (!sphereNodes.empty())
	//		{
	//			SphereNode* currentNode = sphereNodes.back();
	//			sphereNodes.pop_back();

	//			float closestDistance = maxInitialDistance;
	//			SphereNode* closestNode = nullptr;
	//			size_t closestIndex = -1;

	//			for (size_t i = 0; i < sphereNodes.size(); ++i)
	//			{
	//				float distance = CheckSphereDistance(currentNode, sphereNodes[i]);
	//				if (distance < closestDistance)
	//				{
	//					closestDistance = distance;
	//					closestNode = sphereNodes[i];
	//					closestIndex = i;

	//				}
	//			}

	//			if (closestNode)
	//			{
	//				sphereNodes.erase(sphereNodes.begin() + closestIndex);
	//				openList.push_back(CombineNodes(currentNode, closestNode));
	//			}
	//			else
	//			{
	//				openList.push_back(currentNode);
	//			}
	//		}

	//		sphereNodes = openList;
	//		maxInitialDistance = std::numeric_limits<float>::max();
	//	}

	//	return sphereNodes.front();
	//}

	//SphereNode* CombineNodes(SphereNode* leftSphere, SphereNode* rightSphere)
	//{
	//	glm::vec3 minPoint = glm::min(leftSphere->center - glm::vec3(leftSphere->radius), rightSphere->center - glm::vec3(rightSphere->radius));
	//	glm::vec3 maxPoint = glm::max(leftSphere->center + glm::vec3(leftSphere->radius), rightSphere->center + glm::vec3(rightSphere->radius));
	//	glm::vec3 newCenter = (minPoint + maxPoint) * 0.5f;
	//	float newRadius = glm::length(maxPoint - newCenter) * 0.5f;

	//	SphereNode* newNode = new SphereNode{ entt::null, newCenter, newRadius };
	//	newNode->left = leftSphere;
	//	newNode->right = rightSphere;

	//	return newNode;
	//}

	//void TraverseBVH(SphereNode* node, const glm::vec3& center, float radius, std::vector<entt::entity>& nodesHit) 
	//{
	//	if (!node) {
	//		return;
	//	}

	//	float distance = glm::length(node->center - center);
	//	if (distance > (node->radius + radius)) return;


	//	if (node->isLeaf()) {
	//		eeng::Log(" -> broad phase hit entity: entiy %d", int(node->entity));
	//		nodesHit.push_back(node->entity);
	//	}
	//	else {
	//		TraverseBVH(node->left, center, radius,  nodesHit);
	//		TraverseBVH(node->right, center, radius, nodesHit);
	//	}
	//}

	//void CheckBroadAndNarrowPhase(entt::registry& registry) 
	//{
	//	if (!rootNode)
	//		return;
	//	auto view = registry.view<TransformComponent, ColliderComponent>();
	//	for (auto entity : view) {
	//		auto& transform = view.get<TransformComponent>(entity);
	//		auto& collider = view.get<ColliderComponent>(entity);

	//		glm::vec3 center = transform.position + collider.sphere.center;
	//		float radius = collider.sphere.radius;

	//		std::vector<entt::entity> entities;
	//		TraverseBVH(rootNode, center, radius, entities);

	//		for (auto otherEntity : entities) {
	//			if (otherEntity == entity) continue;

	//			auto& otherTransform = view.get<TransformComponent>(otherEntity);
	//			auto& otherCollider = view.get<ColliderComponent>(otherEntity);

	//			glm::vec3 otherCenter = otherTransform.position + otherCollider.sphere.center;
	//			float otherRadius = otherCollider.sphere.radius;

	//			if (CheckSphereCollision(center, radius, otherCenter, otherRadius))
	//			{
	//				collider.sphere.isColliding = true;
	//				otherCollider.sphere.isColliding = true;
	//				//eeng::Log("Collision detected between: %d <-> %d", int(entity), int(otherEntity));
	//				float distance = glm::sqrt(glm::dot(otherCenter - center, otherCenter - center));
	//				if (distance > 0.0001f)
	//				{
	//					float overlap = radius + otherRadius - distance;
	//					glm::vec3 normal = glm::normalize(center - otherCenter);

	//					glm::vec3 correction = normal * (overlap * 0.5f);

	//					auto& transform = registry.get<TransformComponent>(entity);
	//					auto& otherTransform = registry.get<TransformComponent>(otherEntity);

	//					//transform.position = (transform.position + correction);
	//					//otherTransform.position = (otherTransform.position - correction);
	//				}
	//			}
	//		}
	//	}
	//}
/*void Update(entt::registry& registry) {
		auto view = registry.view<ColliderComponent>();
			for (auto entity : view) {
				auto& sphereComponent = view.get<ColliderComponent>(entity);

				sphereComponent.Update(registry);
			}
		BuildLeafNodes(registry);
		CheckBroadAndNarrowPhase(registry);
	}*/
#pragma endregion
	
#pragma region CollisionFromPresentations
	bool TestCollisionSphereSphere(const Sphere& sphereA, const Sphere& sphereB) 
	{
		glm::vec3 centerToCenterDistance = sphereA.center - sphereB.center;
		float distanceSquared = glm::dot(centerToCenterDistance, centerToCenterDistance);

		float radiusSum = sphereA.radius + sphereB.radius;
		return distanceSquared <= (radiusSum * radiusSum);

	}

	bool TestCollisionAABBAABB(const AABBCenterHalfWidths& aabbA, const AABBCenterHalfWidths& aabbB)
	{
		float centerDifference = aabbA.center[0] - aabbB.center[0];
		float compoundedWidth = aabbA.halfWidths[0] + aabbB.halfWidths[0];
		
		if (centerDifference > compoundedWidth) {
			return false;
		}

		centerDifference = aabbA.center[1] - aabbB.center[1];
		compoundedWidth = aabbA.halfWidths[1] + aabbB.halfWidths[1];
		
		if (centerDifference > compoundedWidth) {
			return false;
		}

		centerDifference = aabbA.center[2] - aabbB.center[2];
		compoundedWidth = aabbA.halfWidths[2] + aabbB.halfWidths[2];

		if (centerDifference > compoundedWidth) {
			return false;
		}

		return true;
	}

	void SeparateSpheres(std::shared_ptr<entt::registry> reg, Sphere& a, Sphere& b, SimpleContact* contact) 
	{
		auto& transform = reg->get<TransformComponent>(a.parent);
		auto& otherTransform = reg->get<TransformComponent>(b.parent);
		contact->contactNormal.y = 0;
		transform.position += contact->contactNormal * (contact->penetrationDepth / 2.0f);
		otherTransform.position -= contact->contactNormal * (contact->penetrationDepth / 2.0f);
		delete contact;
	}

	SimpleContact* SphereSphere(Sphere& a, Sphere& b) 
	{
		glm::vec3 centerToCenterDistance = a.center - b.center;
		float distance = glm::dot(centerToCenterDistance, centerToCenterDistance);
		
		float radiiSum = a.radius + b.radius;
		
		if (distance > radiiSum * radiiSum) {
			return nullptr;
		}

		SimpleContact* contact = new SimpleContact();

		contact->contactNormal = glm::normalize(centerToCenterDistance);
		contact->contactPoint = a.center + contact->contactNormal * a.radius;
		contact->penetrationDepth = radiiSum - glm::sqrt(distance);

		return contact;

	}

	float DistanceBetweenCircles(Sphere* leftSphere, Sphere* rightSphere)
	{
		float centerToCenterDistance = glm::length(rightSphere->center - leftSphere->center);

		float surfaceDistance = centerToCenterDistance - (leftSphere->radius + rightSphere->radius);

		return (std::max(0.0f, surfaceDistance));
	}

	void FindMinMaxPoints(glm::vec3 leftCenter, glm::vec3 rightCenter, float leftRadius, float rightRadius, glm::vec3& minOut, glm::vec3& maxOut) {

		minOut.x = std::min(leftCenter.x - leftRadius, rightCenter.x - rightRadius);
		maxOut.x = std::max(leftCenter.x + leftRadius, rightCenter.x + rightRadius);

		minOut.y = std::min(leftCenter.y - leftRadius, rightCenter.y - rightRadius);
		maxOut.y = std::max(leftCenter.x + leftRadius, rightCenter.x + rightRadius);

		minOut.z = std::min(leftCenter.z - leftRadius, rightCenter.z - rightRadius);
		maxOut.z = std::max(leftCenter.z + leftRadius, rightCenter.z + rightRadius);
	}

	SphereNode* BuildNodeFromSingleSphere(Sphere* sphere) {
		return new SphereNode{ sphere, nullptr, nullptr };
	}

	SphereNode* BuildNodeFromSpheres(Sphere* leftSphere, Sphere* rightSphere) {
		glm::vec3 maxPoint, minPoint;
		FindMinMaxPoints(leftSphere->center, rightSphere->center, leftSphere->radius, rightSphere->radius, minPoint, maxPoint);

		glm::vec3 midPoint = (minPoint + (maxPoint - minPoint)) / 2.0f;
		float radius = glm::length(maxPoint - midPoint) / 2.0f;

		return new SphereNode{ new Sphere{midPoint, radius}, nullptr, nullptr };
	}

	std::vector<std::pair<SphereNode*, SphereNode*>> FindPairs(std::vector<SphereNode*>openList, float maxDistance) {
		std::vector<std::pair<SphereNode*, SphereNode*>> allPairs;
		std::vector<SphereNode*> availableSpheres = openList;

		while (!availableSpheres.empty()) {
			SphereNode* currentNode = availableSpheres.back();
			availableSpheres.pop_back();

			float closestDistance = maxDistance;
			SphereNode* closestNode = nullptr;
			int closestIndex = -1;

			for (int i = 0; i < availableSpheres.size(); ++i) {
				float distance = DistanceBetweenCircles(currentNode->collisionRepresentation, availableSpheres[i]->collisionRepresentation);

				if (distance < closestDistance) {
					closestDistance = distance;
					closestNode = availableSpheres[i];
					closestIndex = i;
				}
			}

			if (closestNode) {
				availableSpheres.erase(availableSpheres.begin() + closestIndex);
			}
			allPairs.push_back({ currentNode, closestNode });
		}
		return allPairs;
	}

	SphereNode* BuildBVHBottomUp(std::vector<Sphere*> spheres, float maxDistanceBetweenLeaves) {
		std::vector<SphereNode*> openList;

		for (Sphere* sphere : spheres) {
			openList.push_back(BuildNodeFromSingleSphere(sphere));
		}

		while (openList.size() != 1)
		{
			auto pairs = FindPairs(openList, maxDistanceBetweenLeaves);
			openList.clear();
			for (auto pair : pairs) {
				if (pair.second) {
					auto node = BuildNodeFromSpheres(pair.first->collisionRepresentation, pair.second->collisionRepresentation);
					node->leftChild = pair.first;
					node->rightChild = pair.second;
					openList.push_back(node);
				}
				else {
					auto node = BuildNodeFromSingleSphere(pair.first->collisionRepresentation);
					node->leftChild = pair.first;
					openList.push_back(node);
				}
			}
			maxDistanceBetweenLeaves = std::numeric_limits<float>::max();
		}
		return openList[0];
	}

	std::vector<Sphere*> FindPossibleCollisions(SphereNode* treeRoot, Sphere* sphere) {
		std::vector<Sphere*> possibleCollisions;

		if (!sphere || !treeRoot) {
			return possibleCollisions;
		}

		if (!TestCollisionSphereSphere(*treeRoot->collisionRepresentation, *sphere)) {
			return possibleCollisions;
		}

		if (treeRoot->leftChild == nullptr && treeRoot->rightChild == nullptr) {
			possibleCollisions.push_back(treeRoot->collisionRepresentation);
			return possibleCollisions;
		}

		auto collisions = FindPossibleCollisions(treeRoot->leftChild, sphere);
		possibleCollisions.insert(possibleCollisions.end(), collisions.begin(), collisions.end());

		collisions = FindPossibleCollisions(treeRoot->rightChild, sphere);
		possibleCollisions.insert(possibleCollisions.end(), collisions.begin(), collisions.end());

		return possibleCollisions;
	}

	void Update(std::shared_ptr<entt::registry> registry) {

		spheres.clear();

		auto view = registry->view<ColliderComponent>();
		for (auto entity : view) {
			auto& sphereComponent = view.get<ColliderComponent>(entity);

			sphereComponent.Update(*registry);
			spheres.push_back(&sphereComponent.sphere);
		}
		
		auto root = BuildBVHBottomUp(spheres, 1.0f);
		
		for (auto entity : view) {
			auto& sphereComponent = view.get<ColliderComponent>(entity);
			auto possibleCollisions = FindPossibleCollisions(root, &sphereComponent.sphere);

			for (auto& collision : possibleCollisions) {
				if (collision != &sphereComponent.sphere) {
					SimpleContact* contact = SphereSphere(sphereComponent.sphere, *collision);
					if (contact) {
						SeparateSpheres(registry, sphereComponent.sphere, *collision, contact);

					}
				}
			}
		}

	}
#pragma endregion
};