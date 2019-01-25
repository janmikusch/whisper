#pragma once
#include "stdafx.h"
#include "Collision.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class PhysicsManager
{
public:
	static PhysicsManager& getInstance()
	{
		static PhysicsManager m_instance;
		return m_instance;
	};
	bool AABBvsAABB(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration);
	void findCollisions(std::vector<std::shared_ptr<GameObject>> gameObjects);
	void resolveCollisions();

private:
	PhysicsManager() = default;
	std::vector<Collision> m_manifolds;
};