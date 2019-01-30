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

HeroAnimationComponent::HeroAnimationComponent(std::shared_ptr<GameObject> parent, Layer layer, float animationTime) :
	AnimationComponent(parent, layer, animationTime)
{

}

void HeroAnimationComponent::update( const float fDeltaTimeSeconds)
{
	m_frameTime = m_frameClock.restart();

	std::vector<std::shared_ptr<GameObject>> roomObjects = RoomManager::getInstance().getCurrentRoomObjects();
	std::shared_ptr<GameObject> hitWithSword = nullptr;

	sf::FloatRect currentAttack;

	if (m_currentAnimation == "fightUp")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		currentAttack = attackRects["fightUp"];
		currentAttack.left += m_parent->getPosition().x;
		currentAttack.top += m_parent->getPosition().y;
		hitWithSword = checkCollisions(currentAttack, roomObjects);
	}
	else if (m_currentAnimation == "fightDown")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		currentAttack = attackRects["fightDown"];
		currentAttack.left += m_parent->getPosition().x;
		currentAttack.top += m_parent->getPosition().y;
		hitWithSword = checkCollisions(currentAttack, roomObjects);
	}
	else if (m_currentAnimation == "fightLeft")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		currentAttack = attackRects["fightLeft"];
		currentAttack.left += m_parent->getPosition().x;
		currentAttack.top += m_parent->getPosition().y;
		hitWithSword = checkCollisions(currentAttack, roomObjects);
	}
	else if (m_currentAnimation == "fightRight")
	{
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
		currentAttack = attackRects["fightRight"];
		currentAttack.left += m_parent->getPosition().x;
		currentAttack.top += m_parent->getPosition().y;
		hitWithSword = checkCollisions(currentAttack, roomObjects);
	}
	else
		m_animatedSprite.setPosition(m_parent->getPosition());
	
	if (hitWithSword != nullptr)
		hitWithSword->getComponent<TorchAnimationComponent>()->toggleFlame();

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

	/*sf::Vector2f displacementUp(fightUp.left, fightUp.top);
	sf::FloatRect up = sf::FloatRect(0, 0, fightUp.width, fightUp.height);

	auto bbUp = std::make_shared<BoundingboxComponent>(m_parent, up);
	bbUp->setDisplacement(displacementUp);
	m_parent->addComponent(bbUp);*/

	/*sf::Vector2f displacementDown(fightDown.left, fightDown.top);
	sf::FloatRect down = sf::FloatRect(0, 0, fightDown.width, fightDown.height);

	auto bbDown = std::make_shared<BoundingboxComponent>(m_parent, down);
	bbDown->setDisplacement(displacementDown);
	m_parent->addComponent(bbDown);*/

	/*sf::Vector2f displacementLeft(fightLeft.left, fightLeft.top);
	sf::FloatRect left = sf::FloatRect(0, 0, fightLeft.width, fightLeft.height);

	auto bbLeft = std::make_shared<BoundingboxComponent>(m_parent, left);
	bbLeft->setDisplacement(displacementLeft);
	m_parent->addComponent(bbLeft);*/

	sf::Vector2f displacementRight(fightRight.left, fightRight.top);
	sf::FloatRect Right = sf::FloatRect(0, 0, fightRight.width, fightRight.height);

	auto bbRight = std::make_shared<BoundingboxComponent>(m_parent, Right);
	bbRight->setDisplacement(displacementRight);
	m_parent->addComponent(bbRight);

	//m_parent->addComponent(std::make_shared<BoundingboxComponent>(m_parent, fightDown));
	//m_parent->addComponent(std::make_shared<BoundingboxComponent>(m_parent, fightLeft));
	//m_parent->addComponent(std::make_shared<BoundingboxComponent>(m_parent, fightRight));
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
		{
			std::cout << "true" << std::endl;
			return o;
		}
	}
	return nullptr;
}