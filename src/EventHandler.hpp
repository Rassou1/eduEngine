#pragma once
#include <cstdlib>
#include <cstdint>

enum EventTypes : std::uint8_t
{
	EVENT_STARTED_QUEST,
	EVENT_HORSE_UNKEMPT,
	EVENT_BRUSH_FOUND,
	EVENT_BRUSH_HORSE,
	EVENT_HORSE_BRUSHED,
};


struct Event {
	EventTypes type;
	entt::entity sender;
	entt::entity target;
};
