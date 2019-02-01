#include "stdafx.h"
#include "FadeComponent.h"
#include <iostream>
#include "window.h"

FadeComponent::FadeComponent(std::shared_ptr<GameObject> parent, Layer layer) :
	RenderComponent(parent, layer), EventObserver()
{
	m_rect.setSize(sf::Vector2f{ 960, 704 });
}

void FadeComponent::update(const float
	fDeltaTimeSeconds)
{
	m_rect.setPosition(m_parent->getPosition());
	m_rect.setRotation(m_parent->getRotation());
	m_rect.setOrigin(m_parent->getOrigin());

	if(m_alpha > 0) m_alpha -= fDeltaTimeSeconds * m_speed;
	if(m_alpha < 0)	m_alpha = 0;
	
	auto c = m_rect.getFillColor();
	c.a = static_cast<sf::Uint8>(m_alpha);
	m_rect.setFillColor(c);
}

void FadeComponent::init()
{
	m_rect.setFillColor(sf::Color{ m_rect.getFillColor().r,m_rect.getFillColor().g,m_rect.getFillColor().b,255 });

	m_alpha = 255.0f;
}

void FadeComponent::setPosition(const sf::Vector2f& position)
{
	m_rect.setPosition(position);
}

void FadeComponent::setRotation(float angle)
{
	m_rect.setRotation(angle);
}

void FadeComponent::setScale(const sf::Vector2f& factors)
{
	m_rect.setScale(factors);
}

void FadeComponent::setOrigin(const sf::Vector2f& origin)
{
	m_rect.setOrigin(origin);
}

void FadeComponent::move(const sf::Vector2f& movement)
{
	m_rect.move(movement);
}

void FadeComponent::scale(const sf::Vector2f& factor)
{
	m_rect.scale(factor);
}

void FadeComponent::rotate(float angle)
{
	m_rect.rotate(angle);
}

void FadeComponent::setColor(sf::Color c)
{
	m_rect.setFillColor(c);
}

void FadeComponent::setSpeed(float speed)
{
	m_speed = speed;
}

void FadeComponent::onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent)
{
		m_alpha = 255.0f;
}

void FadeComponent::addToEventBus(engine::EventType e)
{
	if(e == engine::EventType::DAMAGETAKEN)
	{
		EventBus::getInstance().addObserver(e, this);
	}
}


void FadeComponent::draw()
{
	engine::Window::getInstance().getWindow()->draw(m_rect);
	//RenderManagerInstance.AddRenderable(m_layer,SpriteRenderer{&m_sprite});
}
