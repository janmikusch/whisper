#pragma once
#include "stdafx.h"
#include "CharacterMoveBehaviour.h"

class PlayerMoveBehaviour : public CharacterMoveBehaviour
{
public:
	PlayerMoveBehaviour();	
	~PlayerMoveBehaviour() = default;

	sf::Vector2f getMovement() override;
};
