#pragma once
#include "stdafx.h"
#include "InputComponent.h"


class FlipperLeftInputComponent : public InputComponent
{
public:
	explicit FlipperLeftInputComponent(std::shared_ptr<GameObject> parent);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;
};
