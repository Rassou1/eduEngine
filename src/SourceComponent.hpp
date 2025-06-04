#pragma once
#include <entt/entt.hpp>
#include "EventHandler.hpp"
#include "ObserverComponent.hpp"

class SourceComponent {
private:
	
	entt::entity sourceEntity;
protected:
	int numberOfObservers = 0;
	ObserverComponent* observers[256];	

	
public:
	SourceComponent(entt::entity entity) : sourceEntity(entity) {
		for (int i = 0; i < 256; ++i) {
			observers[i] = nullptr;
		}
	}
	void Notify(EventTypes event) {
		for (int i = 0; i < numberOfObservers; ++i) {
			observers[i]->OnNotify(sourceEntity, event);
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

class HorseSource : public SourceComponent {
public:
	
	/*HorseSource(entt::entity entity) : SourceComponent(entity) {
		for (int i = 0; i < 256; ++i) {
			observers[i] = nullptr;
		}
	}*/
	void HorseHungry() {
		Notify(EVENT_HORSE_UNKEMPT);	
	}

	void FeedHorse() {
		Notify(EVENT_BRUSH_HORSE);
	}
};