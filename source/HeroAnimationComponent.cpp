#include "stdafx.h"
#include "HeroAnimationComponent.h"
#include <iostream>
#include "window.h"
#include "TextureManager.h"
#include "CharacterMoveComponent.h"
#include "BoundingBoxComponent.h"
#include "RoomManager.h"
#include "PhysicsManager.h"
#include "ColliderComponent.h"
#include"TorchAnimationComponent.h"
#include "EnemyMoveComponent.h"

HeroAnimationComponent::HeroAnimationComponent(std::shared_ptr<GameObject> parent, Layer layer, float animationTime) :
	AnimationComponent(parent, layer, animationTime)
{

}

void HeroAnimationComponent::update( const float fDeltaTimeSeconds)
{
	m_frameTime = m_frameClock.restart();
	std::vector<std::shared_ptr<GameObject>> roomObjects = RoomManager::getInstance().getCurrentRoomObjects();

	sf::FloatRect currentAttack;

	if (m_currentAnimation == "fightUp")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		currentAttack = attackRects["fightUp"];
		currentAttack.left += m_parent->getPosition().x;
		currentAttack.top += m_parent->getPosition().y;
		m_toggleAble = false;
	}
	else if (m_currentAnimation == "fightDown")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		currentAttack = attackRects["fightDown"];
		currentAttack.left += m_parent->getPosition().x;
		currentAttack.top += m_parent->getPosition().y;
		m_toggleAble = false;
	}
	else if (m_currentAnimation == "fightLeft")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		currentAttack = attackRects["fightLeft"];
		currentAttack.left += m_parent->getPosition().x;
		currentAttack.top += m_parent->getPosition().y;
		m_toggleAble = false;
	}
	else if (m_currentAnimation == "fightRight")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		currentAttack = attackRects["fightRight"];
		currentAttack.left += m_parent->getPosition().x;
		currentAttack.top += m_parent->getPosition().y;
		m_toggleAble = false; 
	}
	else
	{
		m_animatedSprite.setPosition(m_parent->getPosition());
		m_toggleAble = true;
		m_countdown = 0.0f;
	}
	
	if (!m_toggleAble)
	{
		m_countdown += fDeltaTimeSeconds;

		if (m_countdown > 0.5f)
		{
			m_countdown = 0.0f;
			std::shared_ptr<GameObject> hit = checkCollisions(currentAttack, roomObjects);
			if (hit != nullptr)
			{
				hit->getComponent<TorchAnimationComponent>()->toggleFlame();
			}
		}
	}

	std::shared_ptr<GameObject> hitEnemy = checkCollisionsWithEnemies(currentAttack, roomObjects);

	if (hitEnemy != nullptr)
		hitEnemy->getComponent<EnemyMoveComponent>()->setIdle();

	m_animatedSprite.setRotation(m_parent->getRotation());
	m_animatedSprite.setOrigin(m_parent->getOrigin());

	m_animatedSprite.play(*m_animations[m_currentAnimation]);
	m_animatedSprite.update(m_frameTime);
}

void HeroAnimationComponent::init()
{
	AnimationComponent::init();

	sf::FloatRect fightUp = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(64, 40));
	sf::FloatRect fightLeft = sf::FloatRect(sf::Vector2f(-45, 20), sf::Vector2f(62, 30));
	sf::FloatRect fightDown = sf::FloatRect(sf::Vector2f(0, 64), sf::Vector2f(64, 40));
	sf::FloatRect fightRight = sf::FloatRect(sf::Vector2f(46, 20), sf::Vector2f(62, 30));

	attackRects.insert_or_assign("fightUp", fightUp);
	attackRects.insert_or_assign("fightLeft", fightLeft);
	attackRects.insert_or_assign("fightDown", fightDown);
	attackRects.insert_or_assign("fightRight", fightRight);
}

std::shared_ptr<GameObject> HeroAnimationComponent::checkCollisions(sf::FloatRect aabb, std::vector<std::shared_ptr<GameObject>> objects)
{
	for (auto o : objects)
	{
		if (o->getName() != "toggleTorch")
			continue;

		sf::Vector2f n;
		float p;

		if (PhysicsManager::getInstance().AABBvsAABB(aabb, o->getComponent<ColliderComponent>()->getShape(), n, p))
			return o;
	}
	return nullptr;
}

std::shared_ptr<GameObject> HeroAnimationComponent::checkCollisionsWithEnemies(sf::FloatRect aabb, std::vector<std::shared_ptr<GameObject>> objects)
{
	for (auto o : objects)
	{
		if (o->getName() != "enemy")
			continue;

		sf::Vector2f n;
		float p;

		if (PhysicsManager::getInstance().AABBvsAABB(aabb, o->getComponent<ColliderComponent>()->getShape(), n, p))
			return o;
	}
	return nullptr;
}