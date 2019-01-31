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
#include "RoomManager.h"
#include "GUI.h"

GameplayState::GameplayState(StateType type) :State(type)
{
}

State::StateType GameplayState::update(const float fDeltaTimeSeconds)
{
	GameObjectManager& objManager = GameObjectManager::getInstance();
	if (InputManager::getInstance().isKeyDown("EndGame",0))
	{
		EventBus::getInstance().notify(engine::GAMEPAUSE, make_shared<engine::GameEvent>());
		pause(true);
	}

	//TESTING
	if (InputManager::getInstance().isKeyDown(sf::Keyboard::Key::P))
	{
		EventBus::getInstance().notify(engine::DAMAGETAKEN, make_shared<engine::GameEvent>());
	}
	if (InputManager::getInstance().isKeyDown(sf::Keyboard::Key::U))
	{
		RoomManager::getInstance().getCurrentRoom()->setCompleted();
	}

	//ENDTESTING

	if(m_pause)
		return m_type;

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
	m_pause = false;

	engine::GUI::getInstance().init(m_type);

	GameObjectManager& objManager = GameObjectManager::getInstance();

	WorldBuilder::loadTextures("room.tmx");
	auto room = WorldBuilder::loadWorld("room.tmx", sf::Vector2f());

	for(auto it:room)
	{
		objManager.add(it);
	}

	auto topDoor = GameObjectCreator::getInstance().createDoor(Room::Direction::TOP);
	auto rightDoor = GameObjectCreator::getInstance().createDoor(Room::Direction::RIGHT);
	auto bottomDoor = GameObjectCreator::getInstance().createDoor(Room::Direction::BOTTOM);
	auto leftDoor = GameObjectCreator::getInstance().createDoor(Room::Direction::LEFT);

	objManager.add(topDoor);
	objManager.add(rightDoor);
	objManager.add(bottomDoor);
	objManager.add(leftDoor);


	objManager.applyChanges();

	for (auto it : objManager.getList())
	{
		it->init();
	}

	RoomManager::getInstance().init();
}

void GameplayState::exit()
{
	GameObjectManager& objManager = GameObjectManager::getInstance();
	m_pause = false;
	objManager.clear();
}
