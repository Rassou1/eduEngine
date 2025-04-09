#pragma once
#include "glm/glm.hpp"

class NPCControllerComponent 
{
public:
	enum Waypoints
	{
		Waypoint1,
		Waypoint2,
		Waypoint3,
		Count
	};

	glm::vec3 wayPoint1 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 wayPoint2 = glm::vec3(10.0f, 0.0f, 0.0f);
	glm::vec3 wayPoint3 = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 nextWaypoint;

   Waypoints currentWaypoint = Waypoint3;

   NPCControllerComponent() {
       UpdateWaypoint();
   }

   void UpdateWaypoint() {
       // Cycle to next waypoint
       currentWaypoint = static_cast<Waypoints>((currentWaypoint + 1) % Waypoints::Count);

       // Set next target position
       switch (currentWaypoint) {
       case Waypoint1: nextWaypoint = wayPoint1; break;
       case Waypoint2: nextWaypoint = wayPoint2; break;
       case Waypoint3: nextWaypoint = wayPoint3; break;
       }
   }
   
	

};