#include "stdafx.h"
#include "Room.h"
#include "GameObjectManager.h"
#include "EventBus.h"

Room::Room(std::string name): m_name(name),m_completed(false)
{
}

void Room::init()
{
}

bool Room::hasRoom(Direction dir) const
{
	switch (dir) { 
		case TOP:
			return (m_TopRoom != nullptr);
		break;
		case RIGHT:
			return (m_RightRoom != nullptr);
		break;
		case BOTTOM:
			return (m_BottomRoom != nullptr);
		break;
		case LEFT:
			return (m_LeftRoom != nullptr);
		break;
	}
	return false;
}

void Room::setRoom(Direction dir, std::shared_ptr<Room> room)
{
	switch (dir) {
	case TOP:
		m_TopRoom = room;
		break;
	case RIGHT:
		m_RightRoom = room;
		break;
	case BOTTOM:
		m_BottomRoom = room;
		break;
	case LEFT:
		m_LeftRoom = room;
		break;
	}
}

std::shared_ptr<Room> Room::getRoom(Direction dir)
{
	switch (dir) {
	case TOP:
		return m_TopRoom;
		break;
	case RIGHT:
		return m_RightRoom;
		break;
	case BOTTOM:
		return m_BottomRoom;
		break;
	case LEFT:
		return m_LeftRoom;
		break;
	}

	return nullptr;
}

void Room::setRoomObjects(std::vector< std::shared_ptr<GameObject>> roomObjects)
{
	m_roomObjects = roomObjects;
}

void Room::addRoomObjectsToGame()
{
	GameObjectManager& gom = GameObjectManager::getInstance();
	for (auto it : m_roomObjects)
	{
		it->init();
		gom.add(it);
	}
}

void Room::removeRoomObjectsFromGame()
{
	GameObjectManager& gom = GameObjectManager::getInstance();
	for (auto it : m_roomObjects)
	{
		gom.remove(it);
	}
}

void Room::setCompleted(bool state)
{
	m_completed = state;
	EventBus::getInstance().notify(engine::EventType::ROOMCOUNTCHANGED, std::shared_ptr<engine::GameEvent>());
}
