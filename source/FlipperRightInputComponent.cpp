#include "stdafx.h"
#include "FlipperRightInputComponent.h"
#include "InputManager.h"

FlipperRightInputComponent::FlipperRightInputComponent(std::shared_ptr<GameObject> parent):
	InputComponent(parent)
{}

void FlipperRightInputComponent::update(const float fDeltaTimeSeconds)
{
	InputManager& im = InputManager::getInstance();


	if (im.isKeyPressed("FlipperRight", 0))
	{
		m_parent->setRotation(45.0f);
	}
	else
	{
		m_parent->setRotation(-15.0f);
	}
}

void FlipperRightInputComponent::init()
{
	m_parent->setOrigin(sf::Vector2f(50, 0));
	m_parent->setRotation(-15.0f);
}

void FlipperRightInputComponent::draw()
{
}
