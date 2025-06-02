#pragma once
#include <cstdint>
#include <entt/entt.hpp>

enum Events : std::uint8_t
{
	EVENT_HORSE_HUNGRY,
	EVENT_FEED_HORSE,
};

class ObserverComponent {
public:
	virtual ~ObserverComponent() = default;

	virtual void OnNotify(entt::entity& entity, Events event) = 0;
};

class SourceComponent {
private:
	ObserverComponent* observers[256];
	int numberOfObservers = 0;
	entt::entity* sourceEntity;
protected:
	void Notify(Events event) {
		for (int i = 0; i < numberOfObservers; ++i) {
			observers[i]->OnNotify(*sourceEntity, event);
		}
	}
public:
	SourceComponent(entt::entity* entity) : sourceEntity(entity) {
		for (int i = 0; i < 256; ++i) {
			observers[i] = nullptr;
		}
	}
	void AddObserver(ObserverComponent* observer) {
		if (numberOfObservers < 256) {
			observers[numberOfObservers++] = observer;
		}
	};
	void RemoveObserver(ObserverComponent* observer) {
		for (int i = 0; i < numberOfObservers; ++i) {
			if (observers[i] == observer) {
				observers[i] = observers[--numberOfObservers];
				return;
			}
		}
	}
};

class PlayerObserver : ObserverComponent {
public:
	void OnNotify(entt::entity& source, Events event) override {
		switch (event) {
		case EVENT_HORSE_HUNGRY:
			// Handle horse hungry event
			break;
		case EVENT_FEED_HORSE:
			// Handle feed horse event
			break;
		default:
			break;
		}
	}
};

class HorseSource : SourceComponent {
public:

	void HorseHungry() {
		Notify(EVENT_HORSE_HUNGRY);
	}

	void FeedHorse() {
		Notify(EVENT_FEED_HORSE);
	}
};