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

};