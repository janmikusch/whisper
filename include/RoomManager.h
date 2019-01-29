#pragma once
#include "stdafx.h"
#include <memory>;
#include "Room.h"
#include <SFML/System/Err.hpp>
#include "EventObserver.h"
#include "ButtonColor.h"


class RoomManager: public EventObserver
{
public:
	static RoomManager& getInstance();
	void createRooms();
	void init();
	void changeRoom(Room::Direction dir);
	std::shared_ptr<Room> getCurrentRoom() { return  m_currentRoom; };
	int countNotCompleted();
	void onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent) override;
	std::shared_ptr<Room> getRoom(int i);
	void getDamange();
	int getLives() { return m_lives; };

private:
	RoomManager();

	//ButtonRoom
	void createObjectsForButtonRoom(std::vector<std::shared_ptr<GameObject>> &room_objects, int i);
	void createButtons(std::vector<std::shared_ptr<GameObject>> &room_objects, int i);
	void createTorches(std::vector<std::shared_ptr<GameObject>> &room_objects);
	void createButtonRoomComponentObject(std::vector<std::shared_ptr<GameObject>> &room_objects);
	void create3Buttons(std::vector<std::shared_ptr<GameObject>> &room_objects);
	void create4Buttons(std::vector<std::shared_ptr<GameObject>> &room_objects);
	void create5Buttons(std::vector<std::shared_ptr<GameObject>> &room_objects);
	void create6Buttons(std::vector<std::shared_ptr<GameObject>> &room_objects);
	ButtonColor randomColor();

	std::shared_ptr<Room> m_currentRoom;
	std::vector<std::shared_ptr<Room>> m_rooms{};

	int m_lives = 3;
};
