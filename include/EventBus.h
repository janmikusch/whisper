#pragma once
#include "stdafx.h"
#include <vector>
#include <map>
#include "EventObserver.h"
#include <memory>
#include "GameEvent.h"

namespace engine {
	struct GameEvent;
}

class EventObserver;

class EventBus
{
public:
	static EventBus& getInstance();
	void notify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent);

	void addObserver(engine::EventType type, EventObserver* observer);
	void removeObserver(engine::EventType type, EventObserver* observer);
private:
	EventBus() = default;
	std::map<engine::EventType, std::vector<EventObserver*>> m_observers;
};