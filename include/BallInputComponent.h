#pragma once
#include "stdafx.h"
#include "InputComponent.h"


class BallInputComponent : public InputComponent
{
public:
	explicit BallInputComponent(std::shared_ptr<GameObject> parent);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;
};
