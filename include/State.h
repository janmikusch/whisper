#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>


class State
{
public:
	enum StateType { STATE_MENU, STATE_GAMEPLAY };

	virtual ~State() = default;
	State(State::StateType type);
	virtual State::StateType update(const float fDeltaTimeSeconds) = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
	virtual void exit() = 0;

protected:
	State::StateType m_type;
};