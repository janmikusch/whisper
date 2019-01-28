#include "stdafx.h"
#include "DoorComponent.h"
#include <iostream>
#include "window.h"
#include "RoomManager.h"
#include "EventBus.h"

DoorComponent::DoorComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& textureGate, sf::Texture& textureRedDoor, sf::Texture& textureGreenDoor, Room::Direction dir):
	RenderComponent(parent,layer),m_dir(dir)
{
	m_gateSprite.setTexture(textureGate);
	m_reddoorSprite.setTexture(textureRedDoor);
	m_greendoorSprite.setTexture(textureGreenDoor);
}

void DoorComponent::update( const float
	fDeltaTimeSeconds)
{
	m_gateSprite.setPosition(m_parent->getPosition());
	m_gateSprite.setRotation(m_parent->getRotation());
	m_gateSprite.setOrigin(m_parent->getOrigin());

	sf::Vector2f doorOffset{};

	switch (m_dir) { 
	case Room::TOP:
		doorOffset.y += 64;
		break;
	case Room::LEFT:
		doorOffset.x += 64;
		break;
	}
	m_reddoorSprite.setPosition(m_gateSprite.getPosition() + doorOffset);
	m_greendoorSprite.setPosition(m_gateSprite.getPosition() + doorOffset);

}

void DoorComponent::init()
{

}

void DoorComponent::setPosition(const sf::Vector2f& position)
{
	m_gateSprite.setPosition(position);
}

void DoorComponent::setRotation(float angle)
{
	m_gateSprite.setRotation(angle);
}

void DoorComponent::setScale(const sf::Vector2f& factors)
{
	m_gateSprite.setScale(factors);
}

void DoorComponent::setOrigin(const sf::Vector2f& origin)
{
	m_gateSprite.setOrigin(origin);
}

void DoorComponent::move(const sf::Vector2f& movement)
{
	m_gateSprite.move(movement);
}

void DoorComponent::scale(const sf::Vector2f& factor)
{
	m_gateSprite.scale(factor);
}

void DoorComponent::rotate(float angle)
{
	m_gateSprite.rotate(angle);
}

void DoorComponent::onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> gameEvent)
{
	if(collidedWith.getName() != "hero")
	{
		return;
	}

	std::shared_ptr<engine::CollisionGameEvent> cge = std::static_pointer_cast<engine::CollisionGameEvent>(gameEvent);

	if(cge->type != engine::CollisionGameEvent::CollisionType::ENTER)
	{
		return;
	}

	engine::DoorEnterGameEvent doorEvent{};
	if(m_parent->getName()=="door_top")
	{
		doorEvent.direction = Room::Direction::TOP;
	}
	else if (m_parent->getName() == "door_right")
	{
		doorEvent.direction = Room::Direction::RIGHT;
	}
	else if (m_parent->getName() == "door_bottom")
	{
		doorEvent.direction = Room::Direction::BOTTOM;
	}
	else if (m_parent->getName() == "door_left")
	{
		doorEvent.direction = Room::Direction::LEFT;
	}
	else
	{
		return;
	}

	EventBus::getInstance().notify(engine::EventType::DOORENTER, std::make_shared<engine::DoorEnterGameEvent>(doorEvent));
}


void DoorComponent::draw()
{
	auto window = engine::Window::getInstance().getWindow();
	if (RoomManager::getInstance().getCurrentRoom()->hasRoom(m_dir))
	{
		window->draw(m_gateSprite);
		if (!RoomManager::getInstance().getCurrentRoom()->isCompleted())
		{
			window->draw(m_reddoorSprite);
		}
	}
	//draw green room for exit of game
	else if(m_dir == Room::Direction::TOP && RoomManager::getInstance().getCurrentRoom()->getName() == "01" )
	{
		window->draw(m_gateSprite);
		if (RoomManager::getInstance().countNotCompleted() != 0)
		{
			window->draw(m_greendoorSprite);
		}
	}

}
