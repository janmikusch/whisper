#pragma once
#include "stdafx.h"
#include "Component.h"


class EnemyMoveComponent: public Component
{
public:
	enum Direction { UP, DOWN, LEFT, RIGHT };
	enum AnimationState { WALK, IDLE};

	explicit EnemyMoveComponent(const std::shared_ptr<GameObject>& parent, std::shared_ptr<GameObject> target, int character_id = 1);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;
	void dontCollide(sf::Vector2f& movement);
	AnimationState getState() { return m_state; };

	void setTarget(std::shared_ptr<GameObject> target) { m_target = target; };

private:
	void setAnimation(sf::Vector2f movement);
	Direction m_direction;
	int m_characterId;
	AnimationState m_state;
	std::shared_ptr<GameObject> m_target;
	bool isFighting = false;
	sf::Vector2f m_initialPos;
};
