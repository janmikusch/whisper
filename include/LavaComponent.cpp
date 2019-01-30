#include "stdafx.h"
#include "LavaComponent.h"
#include "window.h"

LavaComponent::LavaComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture & texture, sf::IntRect textureRect)
	: SpriteComponent(parent, layer, texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(textureRect);
}

void LavaComponent::update(const float fDeltaTimeSeconds)
{
	m_sprite.setPosition(m_parent->getPosition());
	m_sprite.setRotation(m_parent->getRotation());
	m_sprite.setOrigin(m_parent->getOrigin());
}

void LavaComponent::draw()
{
	if (m_isVisible)
		engine::Window::getInstance().getWindow()->draw(m_sprite);
}

void LavaComponent::init()
{
}

void LavaComponent::setPosition(const sf::Vector2f & position)
{
	SpriteComponent::setPosition(position);
}

void LavaComponent::setRotation(float angle)
{
	SpriteComponent::setRotation(angle);
}

void LavaComponent::setScale(const sf::Vector2f & factors)
{
	SpriteComponent::setScale(factors);
}

void LavaComponent::setOrigin(const sf::Vector2f & origin)
{
	SpriteComponent::setOrigin(origin);
}

void LavaComponent::move(const sf::Vector2f & movement)
{
	SpriteComponent::move(movement);
}

void LavaComponent::scale(const sf::Vector2f & factor)
{
	SpriteComponent::scale(factor);
}

void LavaComponent::rotate(float angle)
{
	SpriteComponent::rotate(angle);
}

void LavaComponent::onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> gameEvent)
{
	if (collidedWith.getName() != "hero")
	{
		return;
	}

	std::shared_ptr<engine::CollisionGameEvent> cge = std::static_pointer_cast<engine::CollisionGameEvent>(gameEvent);

	if (cge->type == engine::CollisionGameEvent::CollisionType::ENTER)
	{
		m_isVisible = true;
		EventBus::getInstance().notify(engine::EventType::DAMAGETAKEN, std::shared_ptr<engine::GameEvent>());
	}
}
