#include "stdafx.h"
#include <iostream>
#include "window.h"
#include "LayerComponent.h"

LayerComponent::LayerComponent(std::shared_ptr<GameObject> parent, Layer layer, float scaleX, float scaleY):
	RenderComponent(parent,layer)
{
	m_sprites = std::vector<std::shared_ptr<sf::Sprite>>{  };
}

void LayerComponent::update( const float fDeltaTimeSeconds)
{
	
}

void LayerComponent::init()
{

}

void LayerComponent::setAllSprites(std::vector<std::shared_ptr<sf::Sprite>> sprites)
{
	m_sprites = sprites;
}

void LayerComponent::addSprite(std::shared_ptr<sf::Sprite> sprite)
{
	m_sprites.push_back(sprite);
}

void LayerComponent::setPosition(const sf::Vector2f& position)
{
	for (auto &sprite : m_sprites)
	{
		sprite->setPosition(position);
	}
}

void LayerComponent::setRotation(float angle)
{
	for (auto &sprite : m_sprites)
	{
		sprite->setRotation(angle);
	}
}

void LayerComponent::setScale(const sf::Vector2f& factors)
{
	for (auto &sprite : m_sprites)
	{
		sprite->setScale(factors);
	}
}

void LayerComponent::setOrigin(const sf::Vector2f& origin)
{
	for (auto &sprite : m_sprites)
	{
		sprite->setOrigin(origin);
	}
}

void LayerComponent::move(const sf::Vector2f& movement)
{
	for (auto &sprite : m_sprites)
	{
		sprite->move(movement);
	}
}

void LayerComponent::scale(const sf::Vector2f& factor)
{
	for (auto &sprite : m_sprites)
	{
		sprite->scale(factor);
	}
}

void LayerComponent::rotate(float angle)
{
	for (auto &sprite : m_sprites)
	{
		sprite->rotate(angle);
	}
}

void LayerComponent::draw()
{
	for(auto sprite : m_sprites)
	{		
		engine::Window::getInstance().getWindow()->draw(*sprite);
	}
}
