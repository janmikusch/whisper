#pragma once
#include "stdafx.h"
#include "CharacterMoveBehaviour.h"

class AiMoveBehaviour : public CharacterMoveBehaviour
{
public:
	AiMoveBehaviour() = default;
	~AiMoveBehaviour() = default;
	sf::Vector2f getMovement() override;
protected:

};
