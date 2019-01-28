#include "stdafx.h"
#include <iostream>
#include "GameplayState.h"
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "TextureManager.h"
#include "LayerComponent.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"
#include "TextGuiComponent.h"
#include "FontManager.h"
#include "window.h"
#include "WorldBuilder.h"

GameplayState::GameplayState(StateType type) :State(type)
{
}

State::StateType GameplayState::update(const float fDeltaTimeSeconds)
{
	GameObjectManager& objManager = GameObjectManager::getInstance();
	if (InputManager::getInstance().isKeyDown("EndGame",0))
	{
		exit();
		return State::StateType::STATE_MENU;
	}

	for (std::shared_ptr<GameObject> o : objManager.getList())
	{
		if(o != nullptr)
			o->update(fDeltaTimeSeconds);
	}

	PhysicsManager::getInstance().findCollisions(objManager.getList());

	objManager.applyChanges();
	return m_type;
}

void GameplayState::draw()
{
	for (std::shared_ptr<GameObject> o : GameObjectManager::getInstance().getList())
	{
		o->draw();
	}
}

void GameplayState::init()
{
	GameObjectManager& objManager = GameObjectManager::getInstance();

	WorldBuilder::loadTextures("room.tmx");
	auto room = WorldBuilder::loadWorld("room.tmx", sf::Vector2f());

	for(auto it:room)
	{
		objManager.add(it);
	}

	objManager.applyChanges();

	for (auto it : objManager.getList())
	{
		it->init();
	}
}

void GameplayState::exit()
{
	GameObjectManager& objManager = GameObjectManager::getInstance();
	
	objManager.clear();
}
