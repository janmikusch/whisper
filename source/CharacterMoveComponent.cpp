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
#include "RandomNumber.h"
#include <SFML/Audio.hpp>
#include "AudioManager.h"
#include "RoomManager.h"

CharacterMoveComponent::CharacterMoveComponent(const std::shared_ptr<GameObject>& parent, int character_id): Component(parent)
{
	m_characterId = character_id;
	m_direction = Direction::DOWN;
}

void CharacterMoveComponent::update(const float fDeltaTimeSeconds)
{
	InputManager& im = InputManager::getInstance();

	auto animComponent = m_parent->getComponent<AnimationComponent>();

	setMoveBehaviour();

	if (RoomManager::getInstance().getLives() == 0 )
	{
		if (!m_isDead)
		{
			m_state = AnimationState::DEATH;
			animComponent->setAnimation("death");
			m_isDead = true;
		}

		if (animComponent->isFinished())
		{
			animComponent->stop();
			m_state = AnimationState::ISDEAD;
		}
	}
	else if(m_moveBehaviour && RoomManager::getInstance().getLives() > 0)
	{	
		if (m_state != AnimationState::ATTACK)
		{
			const float speed = 150.0f;
			sf::Vector2f movement = m_moveBehaviour->getMovement();

			float length = std::sqrt((movement.x * movement.x) + (movement.y * movement.y));
			if (length != 0)
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
				setStandingAnimation();
			}

			if (im.isKeyPressed("Attack", 0) || im.isJoystickButtonPressed(InputManager::JoystickButton::B))
			{
          				setFightAnimation();

				int i = engine::Random::getIntBetween(0, 5);
				switch (i)
				{
				case 0:
					AudioManager::getInstance().playSound("attack1");
					break;
				case 1:
					AudioManager::getInstance().playSound("attack2");
					break;
				case 2:
					AudioManager::getInstance().playSound("attack3");
					break;
				case 3:
					AudioManager::getInstance().playSound("attack4");
					break;
				case 4:
					AudioManager::getInstance().playSound("attack5");
					break;
				default:
					AudioManager::getInstance().playSound("attack6");
					break;
				}
			}
		}
		else if (animComponent->isFinished())
		{
			m_state = AnimationState::WALK;
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
	m_isDead = false;
}

/// set MoveBehaviour if toggle Button is Pressed
void CharacterMoveComponent::setMoveBehaviour()
{
	m_moveBehaviour = std::make_shared<PlayerMoveBehaviour>(PlayerMoveBehaviour{});
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
	for (auto it : GameObjectManager::getInstance().getGameObjectList("enemy"))
	{
		auto charBoundingBox = m_parent->getComponent<ColliderComponent>()->getShape();
		auto otherBoundingBox = it->getComponent<ColliderComponent>()->getShape();

		charBoundingBox.width += movement.x;
		charBoundingBox.height += movement.y;
		charBoundingBox.top += movement.y;
		charBoundingBox.left += movement.x;

		sf::Vector2f normal;
		float penetration;

		if (PhysicsManager::getInstance().AABBvsAABB(charBoundingBox, otherBoundingBox, normal, penetration))
			movement += normal * penetration;
	}
}

void CharacterMoveComponent::setAnimation(sf::Vector2f movement)
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

void CharacterMoveComponent::setStandingAnimation()
{
	auto animComponent = m_parent->getComponent<AnimationComponent>();

	switch (m_direction)
	{
	case UP:
		animComponent->setAnimation("standingUp");
		break;
	case DOWN:
		animComponent->setAnimation("standingDown");
		break;
	case LEFT:
		animComponent->setAnimation("standingLeft");
		break;
	case RIGHT:
		animComponent->setAnimation("standingRight");
		break;
	}

	m_state = AnimationState::STAND;
}

void CharacterMoveComponent::setFightAnimation()
{
	auto animComponent = m_parent->getComponent<AnimationComponent>();

	switch (m_direction)
	{
	case UP:
		animComponent->setAnimation("fightUp");
		break;
	case DOWN:
		animComponent->setAnimation("fightDown");
		break;
	case LEFT:
		animComponent->setAnimation("fightLeft");
		break;
	case RIGHT:
		animComponent->setAnimation("fightRight");
		break;
	}

	m_state = AnimationState::ATTACK;
}
