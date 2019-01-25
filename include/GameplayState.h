#pragma once
#include "stdafx.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include "GameObjectCreator.h"
#include "WorldBuilder.h"

class GameplayState : public State
{
public:
	GameplayState(StateType type);
	State::StateType update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;
	void exit() override;
};
