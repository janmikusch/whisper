#pragma once
#include "stdafx.h"
#include <vector>
#include <memory>
#include "GameObject.h"

class LabyrinthCreator
{
public:
	static void createObjectsForLabyrinthRoom(std::vector<std::shared_ptr<GameObject>> &room_objects);

private:
	LabyrinthCreator() = default;

	static std::string getRandomLabyrinthName();
};
