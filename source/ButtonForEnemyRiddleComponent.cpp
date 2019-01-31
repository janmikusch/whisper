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
	if (collidedWith.getName() != "hero")
		return;

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
			std::shuffle(enemySequence.begin(), enemySequence.end(),e);


			sf::err() << "sequence:";
			//REMOVE AFTER
			for(auto it:enemySequence)
			{
				sf::err() << std::to_string(it);
			}


			nextEnemy = enemySequence.begin();
			enemiesLoaded = true;
		}
	}
	if (cge != nullptr && cge->type == engine::CollisionGameEvent::CollisionType::EXIT)
	{
		for (auto o : RoomManager::getInstance().getCurrentRoomObjects())
		{
			if (o->getName() == "enemy")
				o->getComponent<EnemyMoveComponent>()->setFightingState(true);
		}

		areAttacking = true;
		nextEnemy = enemySequence.begin();
	}
}

void ButtonForEnemyRiddleComponent::update(const float fDeltaTimeSeconds)
{
	ButtonComponent::update(fDeltaTimeSeconds);

	if (m_enemies.empty())
		return;

	if (!areAttacking)
	{
			m_timer += fDeltaTimeSeconds;

		if (m_timer > 1.0f && nextEnemy != enemySequence.end())
		{
			m_enemies[(*nextEnemy)]->getComponent<EnemyMoveComponent>()->setStandingAnimation();
			m_timer = 0;
			nextEnemy++;

			if (nextEnemy == enemySequence.end())
			{
				areAttacking = true;
			}

		}
	}
}

void ButtonForEnemyRiddleComponent::init()
{
	m_timer = 0.0f;
	enemiesLoaded = false;
	areAttacking = false;

	enemySequence.clear();
	enemySequence.push_back(0);
	enemySequence.push_back(1);
	enemySequence.push_back(2);
	enemySequence.push_back(3);
}

void ButtonForEnemyRiddleComponent::enemyAttacked(std::shared_ptr<GameObject> enemy)
{
	if(areAttacking && nextEnemy != enemySequence.end())
	{
		if(enemy == m_enemies[*nextEnemy])
		{
			nextEnemy++;
			if(nextEnemy == enemySequence.end())
				EventBus::getInstance().notify(engine::EventType::ROOMUNLOCKED, std::shared_ptr<engine::GameEvent>());			
		}
		else
		{
			RoomManager::getInstance().resetCurrentRoom();
			EventBus::getInstance().notify(engine::EventType::DAMAGETAKEN, std::shared_ptr<engine::GameEvent>());
			nextEnemy = enemySequence.end();
		}
	}
}
