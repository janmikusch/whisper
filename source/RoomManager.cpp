#include "stdafx.h"
#include "RoomManager.h"
#include "GameObjectManager.h"
#include "FadeComponent.h"
#include "GameObjectCreator.h"
#include "window.h"
#include "Color.h"
#include "RandomNumber.h"
#include "ButtonComponent.h"
#include "ButtonRoomComponent.h"
#include "RigidbodyComponent.h"
#include "ButtonRoomCreator.h"
#include "TorchRoomCreator.h"
#include "LabyrinthCreator.h"
#include "EnemyRoomCreator.h"

RoomManager::RoomManager() :EventObserver()
{
	EventBus::getInstance().addObserver(engine::DOORENTER, this);
	EventBus::getInstance().addObserver(engine::DAMAGETAKEN, this);
	EventBus::getInstance().addObserver(engine::ROOMUNLOCKED, this);

}

RoomManager& RoomManager::getInstance()
{
	static RoomManager instance;
	return instance;
}

void RoomManager::createRooms()
{
	/*
	 * Rooms:
	 *	00	01	02
	 *	10	11	12
	 */
	std::shared_ptr<Room> room_00 = std::make_shared<Room>("00");
	std::shared_ptr<Room> room_01 = std::make_shared<Room>("01");
	std::shared_ptr<Room> room_02 = std::make_shared<Room>("02");
	std::shared_ptr<Room> room_10 = std::make_shared<Room>("10");
	std::shared_ptr<Room> room_11 = std::make_shared<Room>("11");
	std::shared_ptr<Room> room_12 = std::make_shared<Room>("12");

	m_rooms.push_back(room_00);
	m_rooms.push_back(room_01);
	m_rooms.push_back(room_02);
	m_rooms.push_back(room_10);
	m_rooms.push_back(room_11);
	m_rooms.push_back(room_12);

	room_01->setCompleted();
	m_currentRoom = room_01;

	room_00->setRoom(Room::Direction::RIGHT, room_01);
	room_00->setRoom(Room::Direction::BOTTOM, room_10);

	room_01->setRoom(Room::Direction::BOTTOM, room_11);
	room_01->setRoom(Room::Direction::LEFT, room_00);
	room_01->setRoom(Room::Direction::RIGHT, room_02);

	room_02->setRoom(Room::Direction::LEFT, room_01);
	room_02->setRoom(Room::Direction::BOTTOM, room_12);

	room_10->setRoom(Room::Direction::TOP, room_00);
	room_10->setRoom(Room::Direction::RIGHT, room_11);

	room_11->setRoom(Room::Direction::LEFT, room_10);
	room_11->setRoom(Room::Direction::TOP, room_01);
	room_11->setRoom(Room::Direction::RIGHT, room_12);

	room_12->setRoom(Room::Direction::LEFT, room_11);
	room_12->setRoom(Room::Direction::TOP, room_02);

	std::vector<std::shared_ptr<GameObject>> roomObjects_00;
	std::vector<std::shared_ptr<GameObject>> roomObjects_01;
	std::vector<std::shared_ptr<GameObject>> roomObjects_02;
	std::vector<std::shared_ptr<GameObject>> roomObjects_10;
	std::vector<std::shared_ptr<GameObject>> roomObjects_11;
	std::vector<std::shared_ptr<GameObject>> roomObjects_12;

	auto fader = GameObjectCreator::getInstance().createFade();

	roomObjects_00.push_back(fader);
	roomObjects_01.push_back(fader);
	roomObjects_02.push_back(fader);
	roomObjects_10.push_back(fader);
	roomObjects_11.push_back(fader);
	roomObjects_12.push_back(fader);

	ButtonRoomCreator::createObjectsForButtonRoom(roomObjects_00, engine::Random::getIntBetween(3,6));
	TorchRoomCreator::createObjectsForTorchRoom(roomObjects_02);
	LabyrinthCreator::createObjectsForLabyrinthRoom(roomObjects_12);
	EnemyRoomCreator::createObjectsForEnemyRoom(roomObjects_11);


	room_00->setRoomObjects(roomObjects_00);
	room_01->setRoomObjects(roomObjects_01);
	room_02->setRoomObjects(roomObjects_02);
	room_10->setRoomObjects(roomObjects_10);
	room_11->setRoomObjects(roomObjects_11);
	room_12->setRoomObjects(roomObjects_12);
}

void RoomManager::init()
{
	//clear old rooms if left
	auto empty = std::vector<std::shared_ptr<Room>>();
	m_rooms.swap(empty);

	createRooms();

	for(auto it:m_rooms)
	{
		it->init();
	}

	m_lives = 3;
}

void RoomManager::changeRoom(Room::Direction dir)
{
	if(!m_currentRoom->isCompleted())
	{
#ifdef _DEBUG
		sf::err() << "room not solved yet!" << std::endl;
#endif
		return;
	}

	if(!m_currentRoom->hasRoom(dir))
	{
#ifdef _DEBUG
		sf::err() << "no room in this direction!" << std::endl;
#endif
		return; 
	}

	m_currentRoom->removeRoomObjectsFromGame();

#ifdef _DEBUG
	sf::err() << "changed room from " << m_currentRoom->getName();
#endif


	m_currentRoom = m_currentRoom->getRoom(dir);

#ifdef _DEBUG
	sf::err() << " to " << m_currentRoom->getName() << std::endl;
#endif

	m_currentRoom->addRoomObjectsToGame();

	sf::Vector2f newPos { 0,0 };

	switch (dir)
	{
	case Room::TOP:
		newPos.x = 448;
		newPos.y = 512;
		break;
	case Room::RIGHT:
		newPos.x = 128 - 10;
		newPos.y = 320 - 16;
		break;
	case Room::BOTTOM:
		newPos.x = 448;
		newPos.y = 128 - 20;
		break;
	case Room::LEFT:
		newPos.x = 768 + 10;
		newPos.y = 320 - 16;
		break;
	}

	GameObjectManager::getInstance().getFirstGameObject("hero")->setPosition(newPos);
}

int RoomManager::countNotCompleted()
{
	int unsolved = 0;
	for(auto it:m_rooms)
	{
		if(!it->isCompleted())
		{
			unsolved++;
		}
	}
	return unsolved;
}

void RoomManager::resetCurrentRoom()
{
	m_currentRoom->resetRoom();
}

void RoomManager::onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent)
{
	if(type == engine::EventType::DOORENTER)
	{
		std::shared_ptr<engine::DoorEnterGameEvent> ev = std::static_pointer_cast<engine::DoorEnterGameEvent>(gameEvent);

		if(ev != nullptr)
			changeRoom(ev->direction);
	}
	if(type == engine::EventType::DAMAGETAKEN)
	{
		getDamange();
	}
	if (type == engine::EventType::ROOMUNLOCKED)
	{
		getCurrentRoom()->setCompleted(true);
	}
}

void RoomManager::getDamange()
{
	m_lives--;
	if(m_lives == 0)
	{
		EventBus::getInstance().notify(engine::EventType::GAMEOVER, std::make_shared<engine::GameEvent>());
	}
}

std::shared_ptr<Room> RoomManager::getRoom(int i)
{
	return m_rooms[i];
}
