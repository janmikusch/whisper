#include "stdafx.h"
#include "TorchAnimationComponent.h"
#include <iostream>
#include "window.h"
#include "TextureManager.h"
#include "CharacterMoveComponent.h"

TorchAnimationComponent::TorchAnimationComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& handle, float animationTime) :
	AnimationComponent(parent, layer, animationTime)
{
	m_handle.setTexture(handle);
}

void TorchAnimationComponent::update( const float fDeltaTimeSeconds)
{
	m_handle.setPosition(m_parent->getPosition() + m_displace);
	m_handle.setRotation(m_parent->getRotation());
	m_handle.setOrigin(m_parent->getOrigin());

	AnimationComponent::update(fDeltaTimeSeconds);

}

void TorchAnimationComponent::draw()
{
	engine::Window::getInstance().getWindow()->draw(m_handle);
	if (m_activeFlame)
	{
		AnimationComponent::draw();
	}
}

void TorchAnimationComponent::setPosition(const sf::Vector2f & position)
{
	AnimationComponent::setPosition(position);
}

void TorchAnimationComponent::setRotation(float angle)
{
	AnimationComponent::setRotation(angle);

	if (angle == 180)
	{
		m_displace.y = -30;
	}
	else
	{
		m_displace.y = 30;
	}
}

void TorchAnimationComponent::setScale(const sf::Vector2f & factors)
{
	AnimationComponent::setScale(factors);
}

void TorchAnimationComponent::setOrigin(const sf::Vector2f & origin)
{
	AnimationComponent::setOrigin(origin);
}

void TorchAnimationComponent::move(const sf::Vector2f & movement)
{
	AnimationComponent::move(movement);
}

void TorchAnimationComponent::scale(const sf::Vector2f & factor)
{
	AnimationComponent::scale(factor);
}

void TorchAnimationComponent::rotate(float angle)
{
	AnimationComponent::rotate(angle);
}
