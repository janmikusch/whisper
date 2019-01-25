#pragma once
#include "stdafx.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include "GameObject.h"


class MenuState : public State
{
public:
	MenuState(StateType type);
	State::StateType update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;
	void exit() override;
};

