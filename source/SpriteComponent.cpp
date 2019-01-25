#include "stdafx.h"
#include "SpriteComponent.h"
#include <iostream>
#include "window.h"

SpriteComponent::SpriteComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& texture):
	RenderComponent(parent,layer)
{
	m_sprite.setTexture(texture);
}

void SpriteComponent::update( const float
	fDeltaTimeSeconds)
{
	m_sprite.setPosition(m_parent->getPosition());
	m_sprite.setRotation(m_parent->getRotation());
	m_sprite.setOrigin(m_parent->getOrigin());
}

void SpriteComponent::init()
{

}

void SpriteComponent::setPosition(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}

void SpriteComponent::setRotation(float angle)
{
	m_sprite.setRotation(angle);
}

void SpriteComponent::setScale(const sf::Vector2f& factors)
{
	m_sprite.setScale(factors);
}

void SpriteComponent::setOrigin(const sf::Vector2f& origin)
{
	m_sprite.setOrigin(origin);
}

void SpriteComponent::move(const sf::Vector2f& movement)
{
	m_sprite.move(movement);
}

void SpriteComponent::scale(const sf::Vector2f& factor)
{
	m_sprite.scale(factor);
}

void SpriteComponent::rotate(float angle)
{
	m_sprite.rotate(angle);
}


void SpriteComponent::draw()
{
	engine::Window::getInstance().getWindow()->draw(m_sprite);
	//RenderManagerInstance.AddRenderable(m_layer,SpriteRenderer{&m_sprite});
}
