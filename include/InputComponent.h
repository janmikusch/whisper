#pragma once
#include "stdafx.h"
#include "Component.h"


class InputComponent : public Component
{
public:
	explicit InputComponent(std::shared_ptr<GameObject> parent);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;
};
