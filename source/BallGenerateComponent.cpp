#include "stdafx.h"
#include "BallGenerateComponent.h"
#include "InputManager.h"
#include "GameObjectCreator.h"
#include "GameObjectManager.h"
#include "WorldBuilder.h"

BallGenerateComponent::BallGenerateComponent(std::shared_ptr<GameObject> parent, std::string textureSrc, sf::FloatRect rect)
	: Component(parent), m_textureSrc(textureSrc),m_rect(rect)
{
}

void BallGenerateComponent::update(const float fDeltaTimeSeconds)
{
	auto objManager = GameObjectManager::getInstance();

	if(m_applyObservers == true)
	{
		auto ball = objManager.getFirstGameObject("ball");
		if (ball != nullptr)
		{
			WorldBuilder::registerObserver(objManager.getList());

			m_applyObservers = false;
		}
	}

	if (InputManager::getInstance().isKeyDown("CreateBall", 0))
	{
		createBall();
	}
	if (InputManager::getInstance().isKeyDown("RemoveBall", 0))
	{
		destroyBall();
	}
}

void BallGenerateComponent::init()
{
	GameObjectManager::getInstance().add(GameObjectCreator::getInstance().createBall(m_parent->getPosition(), m_textureSrc, m_rect));
	m_applyObservers = true;
}


void BallGenerateComponent::draw()
{
}


void BallGenerateComponent::createBall()
{
	auto objManager = GameObjectManager::getInstance();

	int count = 0;

	for (auto object : objManager.getList())
	{
		if (object->getName() == "ball") count++;
		if (count >= 20) return;
	}

	auto newBall = GameObjectCreator::getInstance().createBall(m_parent->getPosition(), m_textureSrc, m_rect);
	newBall->init();
	GameObjectManager::getInstance().add(newBall);
	m_applyObservers = true;
}

void BallGenerateComponent::destroyBall()
{
	auto objManager = GameObjectManager::getInstance();

	for (auto object : objManager.getList())
	{
		if (object->getName() == "ball")
		{
			objManager.remove(object);
		}
	}
}
