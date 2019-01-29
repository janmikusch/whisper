#pragma once
#include "stdafx.h"
#include <string>
#include "State.h"
#include <map>
#include <SFML/Graphics.hpp>
#include "EventObserver.h"


class GameStateManager : public EventObserver
{
public:
	GameStateManager() = default;
	void update(const float fDeltaTimeSeconds);
	void draw();
	void setState(State::StateType stateName);
	void addState(State::StateType stateName, std::shared_ptr<State> state);

	void onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent) override;
private:
	std::map<State::StateType,std::shared_ptr<State>> m_states;
	State::StateType m_currentState;
};
