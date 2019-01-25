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

	if (im.isKeyPressed("MoveUp", 0))
	{
		movement.y -= 1;
	}

	if (im.isKeyPressed("MoveRight", 0))
	{
		movement.x += 1;
	}

	if (im.isKeyPressed("MoveDown", 0))
	{
		movement.y += 1;
	}

	if (im.isKeyPressed("MoveLeft", 0))
	{
		movement.x -= 1;
	}

	return movement;
}
