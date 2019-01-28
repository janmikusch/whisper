#pragma once
#include "stdafx.h"
#include <memory>;
#include "Room.h"
#include <SFML/System/Err.hpp>
#include "EventObserver.h"


class RoomManager: public EventObserver
{
public:
	static RoomManager& getInstance();
	void createRooms();
	void changeRoom(Room::Direction dir);
	std::shared_ptr<Room> getCurrentRoom() { return  m_currentRoom; };
	int countNotCompleted();
	void onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent) override;

private:
	RoomManager();

	std::shared_ptr<Room> m_currentRoom;
	std::vector<std::shared_ptr<Room>> m_rooms{};
};
