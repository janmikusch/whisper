#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "GameStateManager.h"

class GameObjectCreator
{
public:
	static GameObjectCreator& getInstance();
	void init();

	std::shared_ptr<GameObject> createMap(sf::Vector2f position, std::map<std::string, std::vector<std::shared_ptr<sf::Sprite>>> layers);
	std::shared_ptr<GameObject> createStaticCollider(sf::FloatRect& aabb, sf::Vector2f position = sf::Vector2f());

	std::shared_ptr<GameObject> createCharacter(sf::FloatRect& aabb, int id = 1, sf::Vector2f position = sf::Vector2f());
	std::shared_ptr<GameObject> createCharacterArea(sf::FloatRect& aabb, int id = 1, sf::Vector2f position = sf::Vector2f());


private:
	GameObjectCreator() = default;
};
