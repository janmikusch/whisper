#include "stdafx.h"
#include "WaterComponent.h"
#include "window.h"
#include "RoomManager.h"

WaterComponent::WaterComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture & texture)
	: SpriteComponent(parent, layer, texture)
{
	m_sprite.setTexture(texture);
}

void WaterComponent::update(const float fDeltaTimeSeconds)
{
	m_sprite.setPosition(m_parent->getPosition());
	m_sprite.setRotation(m_parent->getRotation());
	m_sprite.setOrigin(m_parent->getOrigin());

}

void WaterComponent::draw()
{
	if (m_isVisible)
	{
		SpriteComponent::draw();
	}
}

void WaterComponent::init()
{
}

void WaterComponent::setPosition(const sf::Vector2f & position)
{
	SpriteComponent::setPosition(position);
}

void WaterComponent::setRotation(float angle)
{
	SpriteComponent::setRotation(angle);
}

void WaterComponent::setScale(const sf::Vector2f & factors)
{
	SpriteComponent::setScale(factors);
}

void WaterComponent::setOrigin(const sf::Vector2f & origin)
{
	SpriteComponent::setOrigin(origin);
}

void WaterComponent::move(const sf::Vector2f & movement)
{
	SpriteComponent::move(movement);
}

void WaterComponent::scale(const sf::Vector2f & factor)
{
	SpriteComponent::scale(factor);
}

void WaterComponent::rotate(float angle)
{
	SpriteComponent::rotate(angle);
}

void WaterComponent::onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> gameEvent)
{
	if (collidedWith.getName() != "hero")
	{
		return;
	}

	std::shared_ptr<engine::CollisionGameEvent> cge = std::static_pointer_cast<engine::CollisionGameEvent>(gameEvent);

	if (cge->type == engine::CollisionGameEvent::CollisionType::ENTER)
	{
		m_isVisible = true;
	}
}
