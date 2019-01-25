#pragma once
#include "stdafx.h"
#include <string>
#include "State.h"
#include <map>
#include <SFML/Graphics.hpp>


class GameStateManager
{
public:
	GameStateManager() = default;
	void update(const float fDeltaTimeSeconds);
	void draw();
	void setState(State::StateType stateName);
	void addState(State::StateType stateName, std::shared_ptr<State> state);

private:
	std::map<State::StateType,std::shared_ptr<State>> m_states;
	State::StateType m_currentState;
};
