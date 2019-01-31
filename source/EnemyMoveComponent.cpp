#include "stdafx.h"
#include "EnemyMoveComponent.h"
#include "AnimatedSprite.h"
#include "InputManager.h"
#include <valarray>
#include "AnimationComponent.h"
#include "PlayerMoveBehaviour.h"
#include "AiMoveBehaviour.h"
#include "GameObjectManager.h"
#include "CharacterAreaComponent.h"
#include "ColliderComponent.h"
#include "PhysicsManager.h"
#include "RandomNumber.h"
#include <SFML/Audio.hpp>
#include "AudioManager.h"

EnemyMoveComponent::EnemyMoveComponent(const std::shared_ptr<GameObject>& parent, int character_id): Component(parent)
{
	m_characterId = character_id;
	m_direction = Direction::DOWN;
	m_state = AnimationState::IDLE;
}

void EnemyMoveComponent::update(const float fDeltaTimeSeconds)
{
	InputManager& im = InputManager::getInstance();

	auto animComponent = m_parent->getComponent<AnimationComponent>();


	const float speed = 150.0f;
	sf::Vector2f movement = m_parent->getPosition() - m_target->getPosition();

	float length = std::sqrt((movement.x * movement.x) + (movement.y * movement.y));
	if (isFighting)
	{
		m_state = AnimationState::WALK;

		movement = movement / length; //normalize
		movement *= (speed * fDeltaTimeSeconds); // speed up
		setAnimation(movement);

		//keepInArea(movement);
		dontCollide(movement);
		m_parent->move(movement);
	}
	else
	{
		m_state = AnimationState::IDLE;
	}
}

void EnemyMoveComponent::draw()
{
}

void EnemyMoveComponent::init()
{
}

void EnemyMoveComponent::dontCollide(sf::Vector2f& movement)
{
	for(auto it:GameObjectManager::getInstance().getGameObjectList("staticCollider"))
	{
		auto charBoundingBox = m_parent->getComponent<ColliderComponent>()->getShape();
		auto otherBoundingBox = it->getComponent<ColliderComponent>()->getShape();

		charBoundingBox.width += movement.x;
		charBoundingBox.height += movement.y;
		charBoundingBox.top += movement.y;
		charBoundingBox.left += movement.x;

		sf::Vector2f normal;
		float penetration;

		if(PhysicsManager::getInstance().AABBvsAABB(charBoundingBox, otherBoundingBox, normal, penetration))
			movement += normal * penetration;
	}	
	for(auto it:GameObjectManager::getInstance().getGameObjectList("toggleTorch"))
	{
		auto charBoundingBox = m_parent->getComponent<ColliderComponent>()->getShape();
		auto otherBoundingBox = it->getComponent<ColliderComponent>()->getShape();

		charBoundingBox.width += movement.x;
		charBoundingBox.height += movement.y;
		charBoundingBox.top += movement.y;
		charBoundingBox.left += movement.x;

		sf::Vector2f normal;
		float penetration;

		if(PhysicsManager::getInstance().AABBvsAABB(charBoundingBox, otherBoundingBox, normal, penetration))
			movement += normal * penetration;
	}
}

void EnemyMoveComponent::setAnimation(sf::Vector2f movement)
{
	auto animComponent = m_parent->getComponent<AnimationComponent>();
	
	if (animComponent)
	{		
		if(std::abs(movement.y) > std::abs(movement.x))
		{
			//animate up or down
			if (movement.y >= 0)
			{
				animComponent->setAnimation("down");
				m_direction = Direction::DOWN;
			}
			else
			{
				animComponent->setAnimation("up");
				m_direction = Direction::UP;
			}
		}
		else
		{
			if (movement.x <= 0)
			{
				animComponent->setAnimation("left");
				m_direction = Direction::LEFT;
			}
			else
			{
				animComponent->setAnimation("right");
				m_direction = Direction::RIGHT;
			}
		}
	}
}
