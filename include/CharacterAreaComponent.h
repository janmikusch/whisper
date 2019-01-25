#pragma once
#include "stdafx.h"
#include "Component.h"
#include "RenderComponent.h"

class CharacterAreaComponent:public RenderComponent
{
public:
	explicit CharacterAreaComponent(const std::shared_ptr<GameObject>& parent, int id);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;

};
