#pragma once
#include <glm/glm.hpp>
#include "SphereComponent.hpp"
#include "Log.hpp"

struct SimpleContact {
	uint32_t idA;
	uint32_t idB;
	float penetrationDepth;
	glm::vec3 contactPoint;
	glm::vec3 contactNormal;
};

struct SphereNode {
	Sphere* collisionRepresentation;
	SphereNode* leftChild;
	SphereNode* rightChild;
};

class CollisionSystem {

	std::vector<SphereNode*> openList;
	std::vector<Sphere*> spheres;

public:

	CollisionSystem() {};

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

	void SeparateSpheres(Sphere& a, Sphere& b, float penetrationDepth) 
	{
		glm::vec3 collisionNormal = glm::normalize(b.center - a.center);
		a.center -= collisionNormal * (penetrationDepth / 2.0f);
		b.center += collisionNormal * (penetrationDepth / 2.0f);
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

		auto view = registry->view<SphereComponent>();
		for (auto entity : view) {
			auto& sphereComponent = view.get<SphereComponent>(entity);

			sphereComponent.Update(registry);
			spheres.push_back(&sphereComponent.sphere);
		}
		
		auto root = BuildBVHBottomUp(spheres, 50.0f);
		
		for (auto entity : view) {
			auto& sphereComponent = view.get<SphereComponent>(entity);
			auto possibleCollisions = FindPossibleCollisions(root, &sphereComponent.sphere);

			for (auto& collision : possibleCollisions) {
				if (collision != &sphereComponent.sphere) {
					SimpleContact* contact = SphereSphere(sphereComponent.sphere, *collision);
					if (contact) {
						SeparateSpheres(sphereComponent.sphere, *collision, contact->penetrationDepth);
						eeng::Log("Collision detected between spheres");
						std::cout << "Collision detected between spheres: " << sphereComponent.sphere.center.x << " and " << collision->center.x << std::endl;
						delete contact;
					}
				}
			}
		}

	}
};