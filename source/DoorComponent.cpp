#include "stdafx.h"
#include "DoorComponent.h"
#include <iostream>
#include "window.h"

DoorComponent::DoorComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& textureGate, sf::Texture& textureDoor, Room::Direction dir):
	RenderComponent(parent,layer),m_dir(dir)
{
	m_gateSprite.setTexture(textureGate);
	m_doorSprite.setTexture(textureDoor);
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
		doorOffset.y -= 64;
		break;
	case Room::RIGHT:
		doorOffset.x += 64;
		break;
	case Room::BOTTOM:
		doorOffset.y += 64;
		break;
	case Room::LEFT:
		doorOffset.x -= 64;
		break;
	}
	m_doorSprite.setPosition(m_gateSprite.getPosition() + doorOffset);

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
	engine::Window::getInstance().getWindow()->draw(m_gateSprite);
	//RenderManagerInstance.AddRenderable(m_layer,SpriteRenderer{&m_sprite});
}
