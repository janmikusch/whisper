#include "stdafx.h"
#include "PlayerMoveBehaviour.h"
#include "InputManager.h"

PlayerMoveBehaviour::PlayerMoveBehaviour():CharacterMoveBehaviour()
{

}

sf::Vector2f PlayerMoveBehaviour::getMovement()
{	
	InputManager& im = InputManager::getInstance();

	sf::Vector2f movement{0,0};

	if (im.isKeyPressed("Up", 0) || im.getLeftJoystickAxis()== InputManager::StickDirection::UP)
	{
		movement.y -= 1;
	}

	if (im.isKeyPressed("Right", 0) || im.getLeftJoystickAxis() == InputManager::StickDirection::RIGHT)
	{
		movement.x += 1;
	}

	if (im.isKeyPressed("Down", 0) || im.getLeftJoystickAxis() == InputManager::StickDirection::DOWN)
	{
		movement.y += 1;
	}

	if (im.isKeyPressed("Left", 0) || im.getLeftJoystickAxis() == InputManager::StickDirection::LEFT)
	{
		movement.x -= 1;
	}

	return movement;
}
