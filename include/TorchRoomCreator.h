#pragma once
#include "stdafx.h"
#include "Color.h"
#include "GameObject.h"

class TorchRoomCreator
{
public:
	//ButtonRoom
	static void createObjectsForTorchRoom(std::vector<std::shared_ptr<GameObject>> &room_objects);
private:
	static void createTorches(std::vector<std::shared_ptr<GameObject>> &room_objects);
	static void createAnwerObject(std::vector<std::shared_ptr<GameObject>> &room_objects);

	static engine::Color randomTorchColor();

};
