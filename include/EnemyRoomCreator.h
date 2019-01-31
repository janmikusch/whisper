#pragma once
#include "stdafx.h"
#include <vector>
#include <memory>
#include "GameObject.h"

class EnemyRoomCreator
{
public:
	static void createObjectsForEnemyRoom(std::vector<std::shared_ptr<GameObject>> &room_objects);

private:
	EnemyRoomCreator() = default;
};
