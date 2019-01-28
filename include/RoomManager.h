#pragma once
#include "stdafx.h"
#include <memory>;
#include "Room.h"
#include <SFML/System/Err.hpp>


class RoomManager
{
public:
	static RoomManager& getInstance();
	void createRooms();
	void changeRoom(Room::Direction dir);
	std::shared_ptr<Room> getCurrentRoom() { return  m_currentRoom; };
private:
	RoomManager() = default;

	std::shared_ptr<Room> m_currentRoom;
};
