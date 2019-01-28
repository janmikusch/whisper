#pragma once
#include "stdafx.h"
#include "Component.h"
#include "CharacterMoveBehaviour.h"


class CharacterMoveComponent: public Component
{
public:
	enum Direction { UP, DOWN, LEFT, RIGHT };
	enum AnimationState { WALK, STAND, ATTACK};

	explicit CharacterMoveComponent(const std::shared_ptr<GameObject>& parent, int character_id = 1);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;
	void setMoveBehaviour();
	void keepInArea(sf::Vector2f& movement);
	void dontCollide(sf::Vector2f& movement);
	AnimationState getState() { return m_state; };
private:
	void setAnimation(sf::Vector2f movement);
	void setStandingAnimation();
	void setFightAnimation();
	Direction m_direction;
	std::shared_ptr<CharacterMoveBehaviour> m_moveBehaviour;
	int m_characterId;
	AnimationState m_state;
};
