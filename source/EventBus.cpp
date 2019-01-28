#include "stdafx.h"
#include "EventBus.h"

EventBus& EventBus::getInstance()
{
	static EventBus instance;
	return instance;
}

void EventBus::notify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent)
{
	auto it = m_observers.find(type);
	if (it == m_observers.end())
		return;

	auto observers = it->second;

	for (auto observer : observers)
	{
		observer->onNotify(type, gameEvent);
	}
}

void EventBus::addObserver(engine::EventType type, EventObserver* observer)
{
	m_observers[type].push_back(observer);
}

void EventBus::removeObserver(engine::EventType type, EventObserver* observer)
{
	auto position = std::find(m_observers[type].begin(), m_observers[type].end(), observer);

	if (position != m_observers[type].end())
	{
		m_observers[type].erase(position);
	}
}
