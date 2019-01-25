#include "stdafx.h"
#include "BallInputComponent.h"
#include "InputManager.h"
#include "RigidbodyComponent.h"

BallInputComponent::BallInputComponent(std::shared_ptr<GameObject> parent)
	: InputComponent(parent)
{
}

void BallInputComponent::update(const float fDeltaTimeSeconds)
{
	InputManager& im = InputManager::getInstance();

	sf::Vector2f force = { 0.0f,0.0f };
	const float ballSpeed = 10000.0f;


	/*if (im.isKeyPressed("PushBallUp", 0))
	{
		force.y -= 1;
	}
	
	if (im.isKeyPressed("PushBallRight", 0))
	{
		force.x += 1;
	}
	
	if (im.isKeyPressed("PushBallDown", 0))
	{
		force.y += 1;
	}
	
	if (im.isKeyPressed("PushBallLeft", 0))
	{
		force.x -= 1;
	}

	float length = std::sqrt((force.x * force.x) + (force.y * force.y));
	if (length != 0)
	{
		force = force / length; //normalize
		force *= (ballSpeed * fDeltaTimeSeconds); // speed up
		m_parent->getComponent<Rigidbody>()->addImpulse(force);
	}*/
}

void BallInputComponent::init()
{

}

void BallInputComponent::draw()
{
}
