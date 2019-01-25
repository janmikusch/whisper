#pragma once
#include "stdafx.h"
#include "GameObjectCreator.h"
#include <vector>
#include "NLTmxMap.h"
#include <SFML/Graphics.hpp>
#include "GameStateManager.h"

class WorldBuilder
{
public:
	WorldBuilder();
	static std::vector<std::shared_ptr<GameObject>> loadWorld(const string& filename, const sf::Vector2f& offset);
	static void loadTextures(const string& filename);
	static void registerObserver(std::vector<std::shared_ptr<GameObject>> objects);
};