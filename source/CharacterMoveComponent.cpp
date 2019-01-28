#include "stdafx.h"
#include "CharacterMoveComponent.h"
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

CharacterMoveComponent::CharacterMoveComponent(const std::shared_ptr<GameObject>& parent, int character_id): Component(parent)
{
	m_characterId = character_id;
}

void CharacterMoveComponent::update(const float fDeltaTimeSeconds)
{
	setMoveBehaviour();

	if(m_moveBehaviour)
	{
		const float speed = 100.0f;
		sf::Vector2f movement = m_moveBehaviour->getMovement();

		float length = std::sqrt((movement.x * movement.x) + (movement.y * movement.y));
		if (length != 0)
		{
			movement = movement / length; //normalize
			movement *= (speed * fDeltaTimeSeconds); // speed up
			setAnimation(movement);

			//keepInArea(movement);
			dontCollide(movement);
			m_parent->move(movement);
		}
	}
}

void CharacterMoveComponent::draw()
{
}

void CharacterMoveComponent::init()
{
	if (m_characterId == 1)
	{
		m_moveBehaviour = std::make_shared<PlayerMoveBehaviour>(PlayerMoveBehaviour{});
	}
}

/// set MoveBehaviour if toggle Button is Pressed
void CharacterMoveComponent::setMoveBehaviour()
{
	m_moveBehaviour = std::make_shared<PlayerMoveBehaviour>(PlayerMoveBehaviour{});

	/*
	InputManager& im = InputManager::getInstance();

	if (im.isKeyPressed("Toggle1", 0))
	{
		if (m_characterId == 1)
		{
			m_moveBehaviour = std::make_shared<PlayerMoveBehaviour>(PlayerMoveBehaviour{});
		}
		else
		{
			m_moveBehaviour = std::make_shared<AiMoveBehaviour>(AiMoveBehaviour{});
		}
	}
	if (im.isKeyPressed("Toggle2", 0))
	{
		if (m_characterId == 2)
		{
			m_moveBehaviour = std::make_shared<PlayerMoveBehaviour>(PlayerMoveBehaviour{});
		}
		else
		{
			m_moveBehaviour = std::make_shared<AiMoveBehaviour>(AiMoveBehaviour{});
		}
	}
	*/
}

void CharacterMoveComponent::keepInArea(sf::Vector2f& movement)
{
	auto it = GameObjectManager::getInstance().getFirstGameObject("area");

	auto charBoundingBox = m_parent->getComponent<ColliderComponent>()->getShape();
	auto areaBoundingBox = it->getComponent<ColliderComponent>()->getShape();

	if((charBoundingBox.left + movement.x < areaBoundingBox.left) && 
		(charBoundingBox.left > areaBoundingBox.left))
	{
		movement.x = 0;
	}
	if ((charBoundingBox.top + movement.y < areaBoundingBox.top) && 
		(charBoundingBox.top > areaBoundingBox.top))
	{
		movement.y = 0;
	}
	if ((charBoundingBox.left + charBoundingBox.width + movement.x > areaBoundingBox.left + areaBoundingBox.width) && 
		(charBoundingBox.left + charBoundingBox.width < areaBoundingBox.left + areaBoundingBox.width))
	{
		movement.x = 0;
	}
	if ((charBoundingBox.top + charBoundingBox.height + movement.y > areaBoundingBox.top+areaBoundingBox.height) && 
		(charBoundingBox.top + charBoundingBox.height < areaBoundingBox.top + areaBoundingBox.height))
	{
		movement.y = 0;
	}
}

void CharacterMoveComponent::dontCollide(sf::Vector2f& movement)
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
}

void CharacterMoveComponent::setAnimation(sf::Vector2f movement) const
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
			}
			else
			{
				animComponent->setAnimation("up");
			}
		}
		else
		{
			if (movement.x <= 0)
			{
				animComponent->setAnimation("left");
			}
			else
			{
				animComponent->setAnimation("right");
			}
		}
	}
}
