#pragma once
#include "stdafx.h"
#include "InputComponent.h"

class BallGenerateComponent : public Component
{
public:
	explicit BallGenerateComponent(std::shared_ptr<GameObject> parent, std::string textureSrc, sf::FloatRect rect);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;

	void createBall();
	void destroyBall();
private:
	std::string m_textureSrc;
	sf::FloatRect m_rect;

	bool m_applyObservers = false;
};
