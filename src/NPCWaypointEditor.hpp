#pragma once
#include "entt/entt.hpp"
#include "NPCControllerComponent.hpp"
#include "imgui.h"

class NPCWaypointEditor {
public:
    static void ShowWaypointEditor(entt::registry& registry) {
        ImGui::Begin("NPC Waypoint Editor");

        auto view = registry.view<NPCControllerComponent, LinearVelocityComponent>();
        for (auto entity : view) {
            auto& npc = view.get<NPCControllerComponent>(entity);
			auto& linearVelocity = view.get<LinearVelocityComponent>(entity);

            ImGui::Text("Current Target: %s", npc.waypointNames[npc.currentWaypoint].c_str());
            ImGui::Separator();

            auto waypoints = npc.getAllWaypoints();
            for (int i = 0; i < waypoints.size(); i++) {
                ImGui::PushID(i);
                ImGui::Text("%s", npc.waypointNames[i].c_str());
                ImGui::DragFloat3("Position", &(*waypoints[i])[0], 0.1f);
                ImGui::Separator();
                ImGui::PopID();
            }

            if (ImGui::Button("Force Next Waypoint")) {
                npc.UpdateWaypoint();
            }

            ImGui::SliderFloat("NPC X Velocity", &linearVelocity.velocity.x, -50.0f, 50.0f);
            ImGui::SliderFloat("NPC Z Velocity", &linearVelocity.velocity.z, -50.0f, 50.0f);
        }

        ImGui::End();
    }
};