#include "stdafx.h"
#include "HeroAnimationComponent.h"
#include <iostream>
#include "window.h"
#include "TextureManager.h"
#include "CharacterMoveComponent.h"

HeroAnimationComponent::HeroAnimationComponent(std::shared_ptr<GameObject> parent, Layer layer, float animationTime) :
	AnimationComponent(parent, layer, animationTime)
{

}

void HeroAnimationComponent::update( const float fDeltaTimeSeconds)
{
	m_frameTime = m_frameClock.restart();
	
	sf::FloatRect currentAttack;

	if (m_currentAnimation == "fightUp")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		sf::FloatRect attackRect = attackRects["fightUp"];
		currentAttack = sf::FloatRect(attackRect.left + m_parent->getPosition().x, attackRect.top + m_parent->getPosition().y, attackRect.width, attackRect.height);
	}
	else if (m_currentAnimation == "fightDown")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		sf::FloatRect attackRect = attackRects["fightDown"];
		currentAttack = sf::FloatRect(attackRect.left + m_parent->getPosition().x, attackRect.top + m_parent->getPosition().y, attackRect.width, attackRect.height);
	}
	else if (m_currentAnimation == "fightLeft")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		sf::FloatRect attackRect = attackRects["fightLeft"];
		currentAttack = sf::FloatRect(attackRect.left + m_parent->getPosition().x, attackRect.top + m_parent->getPosition().y, attackRect.width, attackRect.height);
	}
	else if (m_currentAnimation == "fightRight")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		sf::FloatRect attackRect = attackRects["fightRight"];
		currentAttack = sf::FloatRect(attackRect.left + m_parent->getPosition().x, attackRect.top + m_parent->getPosition().y, attackRect.width, attackRect.height);
	}
	else
		m_animatedSprite.setPosition(m_parent->getPosition());

	m_animatedSprite.setRotation(m_parent->getRotation());
	m_animatedSprite.setOrigin(m_parent->getOrigin());

	m_animatedSprite.play(*m_animations[m_currentAnimation]);
	m_animatedSprite.update(m_frameTime);
}

void HeroAnimationComponent::init()
{
	AnimationComponent::init();

	sf::FloatRect fightUp = sf::FloatRect(sf::Vector2f(-50, -100), sf::Vector2f(120, 100));
	sf::FloatRect fightLeft = sf::FloatRect(sf::Vector2f(-100, -50), sf::Vector2f(100, 120));
	sf::FloatRect fightDown = sf::FloatRect(sf::Vector2f(-50, 50), sf::Vector2f(120, 100));
	sf::FloatRect fightRight = sf::FloatRect(sf::Vector2f(50, -50), sf::Vector2f(100, 120));

	attackRects.insert_or_assign("fightUp", fightUp);
	attackRects.insert_or_assign("fightLeft", fightLeft);
	attackRects.insert_or_assign("fightDown", fightDown);
	attackRects.insert_or_assign("fightRight", fightRight);
}