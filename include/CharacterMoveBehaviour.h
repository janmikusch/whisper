#pragma once
#include "stdafx.h"
#include <SFML/System/Vector2.hpp>

class CharacterMoveBehaviour
{
public:
	virtual ~CharacterMoveBehaviour() = default;
	CharacterMoveBehaviour() = default;
	virtual sf::Vector2f getMovement() = 0;

};
