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
			std::shuffle(spawningSequence.begin(), spawningSequence.end(),e);

			nextEnemy = spawningSequence.begin();
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
		calcAttackingSequence();
		spawningSequence.clear();
		nextEnemy = attackingSequence.begin();
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

		if (m_timer > 1.0f && nextEnemy != spawningSequence.end())
		{
			m_enemies[(*nextEnemy)]->getComponent<EnemyMoveComponent>()->setStandingAnimation();
			m_timer = 0;
			nextEnemy++;

			if (nextEnemy == spawningSequence.end())
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

	spawningSequence.clear();
	spawningSequence.push_back(0);
	spawningSequence.push_back(1);
	spawningSequence.push_back(2);
	spawningSequence.push_back(3);
}

void ButtonForEnemyRiddleComponent::enemyAttacked(std::shared_ptr<GameObject> enemy)
{
	if(areAttacking && nextEnemy != attackingSequence.end())
	{
		if(enemy == m_enemies[*nextEnemy])
		{
			nextEnemy++;
			if(nextEnemy == attackingSequence.end())
				EventBus::getInstance().notify(engine::EventType::ROOMUNLOCKED, std::shared_ptr<engine::GameEvent>());			
		}
		else
		{
			RoomManager::getInstance().resetCurrentRoom();
			EventBus::getInstance().notify(engine::EventType::DAMAGETAKEN, std::shared_ptr<engine::GameEvent>());
			nextEnemy = spawningSequence.end();
		}
	}
}

void ButtonForEnemyRiddleComponent::calcAttackingSequence()
{
	// Wasser, Feuer, Wind, Erde
	attackingSequence = std::vector<int>();

	int lives = RoomManager::getInstance().getLives();
	for(auto it:spawningSequence)
	{
		attackingSequence.push_back(getCorrectElement(lives, it));
	}
}

int ButtonForEnemyRiddleComponent::getCorrectElement(int lives, int element)
{
	//3 lives
	switch (lives)
	{
	case 3:
		switch (element)
		{
		case 0: // Wasser
			return 3;
		case 1: // Feuer
			return 2;
		case 2: // Wind
			return 0;
		case 3: // Erde
			return 1;
		}
		break;
	case 2:
		switch (element)
		{
		case 0: // Wasser
			return 1;
		case 1: // Feuer
			return 0;
		case 2: // Wind
			return 2;
		case 3: // Erde
			return 3;
		}
		break;
	case 1:
		switch (element)
		{
		case 0: // Wasser
			return 1;
		case 1: // Feuer
			return 0;
		case 2: // Wind
			return 3;
		case 3: // Erde
			return 2;
		}
		break;
	}
	sf::err() << "ERR, cannot calc element" << std::endl;
	return -1;
}
