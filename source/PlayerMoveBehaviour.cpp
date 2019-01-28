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

	if (im.isKeyPressed("Up", 0))
	{
		movement.y -= 1;
	}

	if (im.isKeyPressed("Right", 0))
	{
		movement.x += 1;
	}

	if (im.isKeyPressed("Down", 0))
	{
		movement.y += 1;
	}

	if (im.isKeyPressed("Left", 0))
	{
		movement.x -= 1;
	}

	return movement;
}
