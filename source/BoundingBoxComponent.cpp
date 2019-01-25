#include "stdafx.h"
#include "BoundingBoxComponent.h"
#include <iostream>
#include "window.h"
#include "BoundingBoxComponent.h"

BoundingboxComponent::BoundingboxComponent(std::shared_ptr<GameObject> parent, sf::FloatRect& aabb, Layer layer):
	RenderComponent(parent,layer)
{
	m_debugGeometry = sf::RectangleShape({ aabb.width, aabb.height });
	m_debugGeometry.setFillColor(sf::Color::Transparent);
	m_debugGeometry.setOutlineColor(sf::Color::Red);
	m_debugGeometry.setOutlineThickness(1);
}

void BoundingboxComponent::setColor(sf::Color c)
{
	m_debugGeometry.setOutlineColor(c);
}

void BoundingboxComponent::update( const float
	fDeltaTimeSeconds)
{
	m_debugGeometry.setPosition(m_parent->getPosition());
	m_debugGeometry.setRotation(m_parent->getRotation());
	m_debugGeometry.setOrigin(m_parent->getOrigin());
	setColor(sf::Color::Red);
}

void BoundingboxComponent::init()
{

}

void BoundingboxComponent::setPosition(const sf::Vector2f& position)
{
	m_debugGeometry.setPosition(position);
}

void BoundingboxComponent::setRotation(float angle)
{
	m_debugGeometry.setRotation(angle);
}

void BoundingboxComponent::setScale(const sf::Vector2f& factors)
{
	m_debugGeometry.setScale(factors);
}

void BoundingboxComponent::setOrigin(const sf::Vector2f& origin)
{
	m_debugGeometry.setOrigin(origin);
}

void BoundingboxComponent::move(const sf::Vector2f& movement)
{
	m_debugGeometry.move(movement);
}

void BoundingboxComponent::scale(const sf::Vector2f& factor)
{
	m_debugGeometry.scale(factor);
}

void BoundingboxComponent::rotate(float angle)
{
	m_debugGeometry.rotate(angle);
}


void BoundingboxComponent::draw()
{
	engine::Window::getInstance().getWindow()->draw(m_debugGeometry);
}
