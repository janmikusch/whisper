#pragma once
#include "stdafx.h"
#include "EventBus.h"
#include "GameEvent.h"


class EventObserver
{
public:
	virtual void onNotify(engine::EventType type,std::shared_ptr<engine::GameEvent> gameEvent) = 0;
};
