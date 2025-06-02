#pragma once
#include <functional>
#include "string"
#include "array"

using Listener = std::function<void(std::string)>;
class EventQueue {
private:
	std::array<std::pair<std::uint8_t, Listener>, 256> listeners;
	std::array<std::string, 256> queuedEvents;
	std::uint8_t numberOfQueuedEvents;	

public:
	EventQueue() {
		numberOfQueuedEvents = 0;
		int ID = 0;
		for (auto &pair : listeners) {
			pair.first = ID++;
		}
	}

	std::uint8_t RegisterListener(Listener listener) 
	{
		for (auto& pair : listeners) {
			if (!pair.second) {
				pair.second = listener;
				return pair.first;
			}
		}
		return 255;
	}

	void DeregisterListener(std::uint8_t listenerId) {
		listeners[listenerId].second = nullptr;
	}

	void EnqueueEvent(std::string event) {
		if (numberOfQueuedEvents = 255) return;
		queuedEvents[numberOfQueuedEvents++] = event;
	}
	void BroadcastAllEvents() {
		for (int i = 0; i != numberOfQueuedEvents; ++i) {
			for (auto& pair : listeners) {
				if (pair.second) {
					pair.second(queuedEvents[i]);
				}
			}
			numberOfQueuedEvents = 0;
		}
	}
};