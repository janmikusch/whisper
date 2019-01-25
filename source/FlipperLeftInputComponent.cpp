#include "stdafx.h"
#include "FlipperLeftInputComponent.h"
#include "InputManager.h"
#include <iostream>

FlipperLeftInputComponent::FlipperLeftInputComponent(std::shared_ptr<GameObject> parent):
	InputComponent(parent)
{}

void FlipperLeftInputComponent::update(const float fDeltaTimeSeconds)
{
	InputManager& im = InputManager::getInstance();

	if (im.isKeyPressed("FlipperLeft",0))
	{
		m_parent->setRotation(-45.0f);
	}
	else
	{
		m_parent->setRotation(15.0f);
	}
}

void FlipperLeftInputComponent::init()
{

}

void FlipperLeftInputComponent::draw()
{
}
