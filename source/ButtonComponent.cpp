#include "stdafx.h"
#include "ButtonComponent.h"
#include <iostream>
#include "window.h"
#include "RoomManager.h"
#include "EventBus.h"

ButtonComponent::ButtonComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& texture) :
	RenderComponent(parent, layer)
{
	m_buttonPressed.setTexture(texture);
	m_buttonReleased.setTexture(texture);

	m_buttonReleased.setTextureRect(sf::IntRect(0, 0, 64, 64));
	m_buttonPressed.setTextureRect(sf::IntRect(64, 0, 64, 64));

	m_currentState = m_buttonReleased;
}

void ButtonComponent::update( const float fDeltaTimeSeconds)
{
	if (m_isPressed)
		m_currentState = m_buttonPressed;
	else
		m_currentState = m_buttonReleased;

	m_currentState.setPosition(m_parent->getPosition());
	m_currentState.setRotation(m_parent->getRotation());
	m_currentState.setOrigin(m_parent->getOrigin());
}

void ButtonComponent::init()
{

}

void ButtonComponent::setPosition(const sf::Vector2f& position)
{
	m_currentState.setPosition(position);
}

void ButtonComponent::setRotation(float angle)
{
	m_currentState.setRotation(angle);
}

void ButtonComponent::setScale(const sf::Vector2f& factors)
{
	m_currentState.setScale(factors);
}

void ButtonComponent::setOrigin(const sf::Vector2f& origin)
{
	m_currentState.setOrigin(origin);
}

void ButtonComponent::move(const sf::Vector2f& movement)
{
	m_currentState.move(movement);
}

void ButtonComponent::scale(const sf::Vector2f& factor)
{
	m_currentState.scale(factor);
}

void ButtonComponent::rotate(float angle)
{
	m_currentState.rotate(angle);
}

void ButtonComponent::onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> gameEvent)
{
	if(collidedWith.getName() != "hero")
	{
		return;
	}

	std::shared_ptr<engine::CollisionGameEvent> cge = std::static_pointer_cast<engine::CollisionGameEvent>(gameEvent);

	if(cge->type == engine::CollisionGameEvent::CollisionType::ENTER)
		m_isPressed = true;

	if (cge->type == engine::CollisionGameEvent::CollisionType::EXIT)
		m_isPressed = false;
}


void ButtonComponent::draw()
{
	auto window = engine::Window::getInstance().getWindow();

	window->draw(m_currentState);
}
