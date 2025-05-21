#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Sphere {
	glm::vec3 center;
	float radius;
};

struct AABBCenterHalfWidths {
	glm::vec3 center;
	float halfWidths[3];
};


class SphereComponent {

public:

	std::vector<glm::ivec2> FindMinMaxValues(const std::vector<glm::vec3*> points, int numberOfPoints)
	{
		glm::ivec2 minMaxX = { 0, 0 };
		glm::ivec2 minMaxY = { 0, 0 };
		glm::ivec2 minMaxZ = { 0, 0 };

		for (int i = 0; i != numberOfPoints; ++i)
		{
			if (points[i]->x < points[minMaxX.x]->x)
				minMaxX.x = i;
			if (points[i]->x > points[minMaxX.y]->x)
				minMaxX.y = i;

			if (points[i]->y < points[minMaxY.x]->y)
				minMaxY.x = i;
			if (points[i]->y > points[minMaxY.y]->y)
				minMaxY.y = i;

			if (points[i]->z < points[minMaxZ.x]->z)
				minMaxZ.x = i;
			if (points[i]->z > points[minMaxZ.y]->z)
				minMaxZ.y = i;
		}

		return { minMaxX, minMaxY, minMaxZ };

	}

	glm::ivec2 FindMostDistantPoints(const std::vector<glm::ivec2>& minMaxPoints, const std::vector<glm::vec3*> points)
	{
		glm::vec3 xVec = *points[minMaxPoints[0].y] - *points[minMaxPoints[0].x];
		float xDistance = glm::sqrt(glm::dot(xVec, xVec));

		glm::vec3 yVec = *points[minMaxPoints[1].y] - *points[minMaxPoints[1].x];
		float yDistance = glm::sqrt(glm::dot(yVec, yVec));

		glm::vec3 zVec = *points[minMaxPoints[2].y] - *points[minMaxPoints[2].x];
		float zDistance = glm::sqrt(glm::dot(zVec, zVec));

		glm::ivec2 maxDistance = minMaxPoints[0];

		if (yDistance > xDistance && yDistance > zDistance)
			maxDistance = minMaxPoints[1];

		if (zDistance > xDistance && zDistance > yDistance)
			maxDistance = minMaxPoints[2];

		return maxDistance;
	}

	Sphere BuildSphereFromPoints(const std::vector<glm::vec3*> points, int numberOfPoints)
	{
		auto minMaxVectors = FindMinMaxValues(points, numberOfPoints);

		auto maxDistance = FindMostDistantPoints(minMaxVectors, points);

		Sphere s;

		s.center = (*points[maxDistance.x] + *points[maxDistance.y]) / 2.0f;

		glm::vec3 difference = *points[maxDistance.x] - *points[maxDistance.y];

		s.radius = glm::sqrt(glm::dot(difference, difference)) / 2.0f;

		return s;
	}

	Sphere BuildSphereFromAABB(const AABBCenterHalfWidths& aabb)
	{
		Sphere s;

		s.center = aabb.center;

		//fix
		s.radius = glm::sqrt(
			aabb.halfWidths[0] * aabb.halfWidths[0] +
			aabb.halfWidths[1] * aabb.halfWidths[1] +
			aabb.halfWidths[2] * aabb.halfWidths[2]
		);

		return s;
	}

	AABBCenterHalfWidths BuildAABBFromPoints(const std::vector<glm::vec3*> points, int numberOfPoints)
	{
		auto minMaxVectors = FindMinMaxValues(points, numberOfPoints);

		glm::vec3 minPoint = (*points[minMaxVectors[0].x], *points[minMaxVectors[1].x], *points[minMaxVectors[2].x]);

		glm::vec3 maxPoint = (*points[minMaxVectors[0].y], *points[minMaxVectors[1].y], *points[minMaxVectors[2].x]);

		AABBCenterHalfWidths aabb;

		aabb.center = (minPoint + maxPoint) / 2.0f;

		for (int i = 0; i != 3; ++i) {
			aabb.halfWidths[i] = (maxPoint[i] - minPoint[i]) / 2.0f;
		}

		return aabb;
	}

	AABBCenterHalfWidths BuildAABBFromSphere(const Sphere& sphere)
	{
		AABBCenterHalfWidths aabb;

		aabb.center = sphere.center;

		for (int i = 0; i != 3; ++i) {
			aabb.halfWidths[i] = sphere.radius;
		}

		return aabb;
	}
	
	Sphere sphere;
	AABBCenterHalfWidths aabb;

	SphereComponent() {};

	void Update(std::shared_ptr<entt::registry> registry) {

		auto view = registry->view<SphereComponent>();
		for (auto entity : view) {
			auto& sphereComponent = view.get<SphereComponent>(entity);
			auto& transform = registry->get<TransformComponent>(entity);

			sphereComponent.aabb = BuildAABBFromPoints(transform.GetAABBPoints(), 8);
			sphereComponent.sphere = BuildSphereFromAABB(aabb);
		}
	}
};