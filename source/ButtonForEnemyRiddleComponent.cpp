#include "stdafx.h"
#include "ButtonComponent.h"
#include <iostream>
#include "window.h"
#include "RoomManager.h"
#include "EventBus.h"
#include "ButtonForEnemyRiddleComponent.h"
#include "EnemyMoveComponent.h"
#include <random>
#include <chrono>

ButtonForEnemyRiddleComponent::ButtonForEnemyRiddleComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& texture, engine::Color c, int id) :
	ButtonComponent(parent, layer, texture, c, id)
{
	m_buttonPressed.setTexture(texture);
	m_buttonReleased.setTexture(texture);

	m_buttonReleased.setTextureRect(sf::IntRect(0, 0, 64, 64));
	m_buttonPressed.setTextureRect(sf::IntRect(64, 0, 64, 64));

	m_currentState = m_buttonReleased;
}


void ButtonForEnemyRiddleComponent::onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> gameEvent)
{
	ButtonComponent::onNotify(collidedWith, gameEvent);
	auto cge = std::static_pointer_cast<engine::CollisionGameEvent>(gameEvent);

	if (cge != nullptr && cge->type == engine::CollisionGameEvent::CollisionType::ENTER)
	{
		if (!enemiesLoaded)
		{
			std::vector<std::shared_ptr<GameObject>> emptyvec;
			m_enemies.swap(emptyvec);

			for (auto o : RoomManager::getInstance().getCurrentRoomObjects())
			{
				if (o->getName() == "enemy")
					m_enemies.push_back(o);
			}

			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::default_random_engine e(seed);
			std::shuffle(m_enemies.begin(), m_enemies.end(),e);

			nextEnemy = m_enemies.begin();
			enemiesLoaded = true;
			areAttacking = true;
			nextEnemy = m_enemies.begin();
		}
	}
	if (cge != nullptr && cge->type == engine::CollisionGameEvent::CollisionType::EXIT)
	{
		for (auto o : RoomManager::getInstance().getCurrentRoomObjects())
		{
			if (o->getName() == "enemy")
				o->getComponent<EnemyMoveComponent>()->setFightingState(true);
		}
	}
}

void ButtonForEnemyRiddleComponent::update(const float fDeltaTimeSeconds)
{
	ButtonComponent::update(fDeltaTimeSeconds);

	if (m_enemies.empty())
		return;

	if (!areAttacking)
	{
		if (nextEnemy != m_enemies.end())
			m_timer += fDeltaTimeSeconds;

		if (m_timer > 1.0f && nextEnemy != m_enemies.end())
		{
			(*nextEnemy)->getComponent<EnemyMoveComponent>()->setStandingAnimation();
			m_timer = 0;
			nextEnemy++;
		}
	}
}

void ButtonForEnemyRiddleComponent::init()
{
	m_timer = 0.0f;
	enemiesLoaded = false;
	areAttacking = false;
}

void ButtonForEnemyRiddleComponent::enemyAttacked(std::shared_ptr<GameObject> enemy)
{
	if(areAttacking && nextEnemy != m_enemies.end())
	{
		if(enemy == *nextEnemy)
		{
			nextEnemy++;
			if(nextEnemy == m_enemies.end())
				EventBus::getInstance().notify(engine::EventType::ROOMUNLOCKED, std::shared_ptr<engine::GameEvent>());
		}
		else
		{
			RoomManager::getInstance().resetCurrentRoom();
			EventBus::getInstance().notify(engine::EventType::DAMAGETAKEN, std::shared_ptr<engine::GameEvent>());
		}
	}
}
