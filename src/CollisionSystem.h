#pragma once
#include <glm/glm.hpp>
#include "SphereComponent.hpp"

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

	CollisionSystem() = default;

public:

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

		return allPairs;
	}

};