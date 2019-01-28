#include "stdafx.h"
#include "DoorComponent.h"
#include <iostream>
#include "window.h"
#include "RoomManager.h"

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
