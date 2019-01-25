#include "stdafx.h"
#include "ColliderComponent.h"
#include "RenderManager.h"
#include "window.h"

ColliderComponent::ColliderComponent(std::shared_ptr<GameObject> parent, const sf::FloatRect& aabb, bool isTrigger) : 
	Component(parent), m_shape(aabb)
{
	m_isTrigger = isTrigger;
}

void ColliderComponent::update(const float fDeltaTimeSeconds)
{
	
}

void ColliderComponent::draw()
{

}

void ColliderComponent::init()
{
}

std::shared_ptr<Rigidbody> ColliderComponent::getRigidbody()
{
	if(m_rigidbody== nullptr)
	{
		auto rigidbody = m_parent->getComponent<Rigidbody>();
		if (rigidbody == nullptr)
			sf::err() << "no rigidbody found" << std::endl;
	}
	return m_rigidbody;
}

bool ColliderComponent::isTrigger()
{
	return m_isTrigger;
}

void ColliderComponent::setPosition(const sf::Vector2f& position)
{
	m_shape.left = position.x;
	m_shape.top = position.y;
}

void ColliderComponent::setRotation(float angle)
{
	sf::err() << "setRotation not implemented";
}

void ColliderComponent::setScale(const sf::Vector2f& factors)
{
	sf::err() << "setScale not implemented";
}

void ColliderComponent::setOrigin(const sf::Vector2f& origin)
{
	sf::err() << "setOrigin not implemented";
}

void ColliderComponent::move(const sf::Vector2f& movement)
{
	m_shape.left += movement.x;
	m_shape.top += movement.y;
}

void ColliderComponent::scale(const sf::Vector2f& factor)
{
	sf::err() << "scale not implemented";
}

void ColliderComponent::rotate(float angle)
{
	sf::err() << "rotate not implemented";
}
