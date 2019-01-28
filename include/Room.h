#pragma once
#include "stdafx.h"
#include "memory"
#include <vector>
#include "GameObject.h"

class Room
{
public:
	Room(std::string name);

	enum Direction {TOP,RIGHT,BOTTOM,LEFT};
	bool hasRoom(Direction dir) const;
	void setRoom(Direction dir, std::shared_ptr<Room> room);
	std::shared_ptr<Room> getRoom(Direction dir);

	void setRoomObjects(std::vector< std::shared_ptr<GameObject>> roomObjects);
	void addRoomObjectsToGame();
	void removeRoomObjectsFromGame();

	std::string getName() { return m_name; };

	bool isCompleted() { return m_completed; };
	void setCompleted(bool state = true) { m_completed = state; };

private:
	std::string m_name;

	std::shared_ptr<Room> m_LeftRoom;
	std::shared_ptr<Room> m_TopRoom;
	std::shared_ptr<Room> m_RightRoom;
	std::shared_ptr<Room> m_BottomRoom;

	std::vector<std::shared_ptr<GameObject>> m_roomObjects{};

	bool m_completed;
};
