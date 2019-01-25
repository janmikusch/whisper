#pragma once
#include "stdafx.h"
#include <SFML/System/Vector2.hpp>
#include <memory>

class Rigidbody;

struct Collision
{
public:
	std::shared_ptr<Rigidbody> body1;
	std::shared_ptr<Rigidbody> body2;

	float penetration;
	sf::Vector2f normal;
};
