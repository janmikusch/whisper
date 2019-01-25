#pragma once
#include "stdafx.h"
#include "InputComponent.h"


class FlipperRightInputComponent : public InputComponent
{
public:
	explicit FlipperRightInputComponent(std::shared_ptr<GameObject> parent);

	void update( const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;
};
