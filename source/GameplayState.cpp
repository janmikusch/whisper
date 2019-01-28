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


	//TESTING

	engine::DoorEnterGameEvent doorEvent{};
	if (InputManager::getInstance().isKeyDown(sf::Keyboard::W))
	{
		doorEvent.direction = Room::Direction::TOP;
		EventBus::getInstance().notify(engine::EventType::DOORENTER, std::make_shared<engine::DoorEnterGameEvent>(doorEvent));
	}
	else if (InputManager::getInstance().isKeyDown(sf::Keyboard::D))
	{
		doorEvent.direction = Room::Direction::RIGHT;
		EventBus::getInstance().notify(engine::EventType::DOORENTER, std::make_shared<engine::DoorEnterGameEvent>(doorEvent));
	}
	else if (InputManager::getInstance().isKeyDown(sf::Keyboard::S))
	{
		doorEvent.direction = Room::Direction::BOTTOM;
		EventBus::getInstance().notify(engine::EventType::DOORENTER, std::make_shared<engine::DoorEnterGameEvent>(doorEvent));
	}
	else if (InputManager::getInstance().isKeyDown(sf::Keyboard::A))
	{
		doorEvent.direction = Room::Direction::LEFT;
		EventBus::getInstance().notify(engine::EventType::DOORENTER, std::make_shared<engine::DoorEnterGameEvent>(doorEvent));
	}


	//ENDTESTING

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
}

void GameplayState::exit()
{
	GameObjectManager& objManager = GameObjectManager::getInstance();
	
	objManager.clear();
}
