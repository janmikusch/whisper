#pragma once
#include "stdafx.h"
#include "Component.h"


class CameraComponent : public Component
{
public:
	explicit CameraComponent(std::shared_ptr<GameObject> parent);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void setTarget(std::shared_ptr<GameObject> target);
	void init();
	void reset();
private:
	sf::View m_view;
};