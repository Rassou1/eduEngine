#pragma once
#include <cstdint>
#include <entt/entt.hpp>
#include "EventHandler.hpp"
#include "EventQueue.hpp"
#include "Log.hpp"


class ObserverComponent {
public:
	virtual ~ObserverComponent() = default;

	virtual void OnNotify(entt::entity entity, EventTypes event) = 0;
};



class QuestObserver : ObserverComponent {
public:

	void update(const EventQueue& eventQueue) {
		for (const auto& event : eventQueue.getEvents())
		{
			OnNotify(event.sender, event.type);
		}
	}

	enum class QuestProgression {
		NotStarted,
		Started,
		HorseNeedsBrushing,
		BrushInInventory,
		BrushingHorse,
		QuestCompleted
	};

	QuestProgression getProgress() const {
		return progress;
	}

	void OnNotify(entt::entity source, EventTypes event) override {
		
		switch (event) {
		case EventTypes::EVENT_STARTED_QUEST:
			progress = QuestProgression::Started;
			eeng::Log("Quest started by entity %d", int(source));
			break;
		case EventTypes::EVENT_HORSE_UNKEMPT:
			progress = QuestProgression::HorseNeedsBrushing;
			eeng::Log("Horse needs brushing");
			break;
		case EventTypes::EVENT_BRUSH_FOUND:
			progress = QuestProgression::BrushInInventory;
			eeng::Log("Brush picked up by entity %d", int(source));
			break;
		case EventTypes::EVENT_BRUSH_HORSE:
			progress = QuestProgression::BrushingHorse;
			eeng::Log("Horse brushed by entity %d", int(source));
			break;
		case EventTypes::EVENT_HORSE_BRUSHED:
			progress = QuestProgression::QuestCompleted;
			eeng::Log("Quest complete.");
			break;
		default:
			break;
		}

	}

private:
	QuestProgression progress = QuestProgression::NotStarted;
};

