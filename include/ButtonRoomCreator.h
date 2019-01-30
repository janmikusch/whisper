#pragma once
#include "stdafx.h"
#include "Color.h"
#include "GameObject.h"

class ButtonRoomCreator
{
public:
	//ButtonRoom
	static void createObjectsForButtonRoom(std::vector<std::shared_ptr<GameObject>> &room_objects, int i);
private:
	static void createButtons(std::vector<std::shared_ptr<GameObject>> &room_objects, int i);
	static void createTorches(std::vector<std::shared_ptr<GameObject>> &room_objects);
	static void createButtonRoomChecker(std::vector<std::shared_ptr<GameObject>> &room_objects, int i);
	static void create3Buttons(std::vector<std::shared_ptr<GameObject>> &room_objects);
	static void create4Buttons(std::vector<std::shared_ptr<GameObject>> &room_objects);
	static void create5Buttons(std::vector<std::shared_ptr<GameObject>> &room_objects);
	static void create6Buttons(std::vector<std::shared_ptr<GameObject>> &room_objects);

	static std::shared_ptr<GameObject> calcCorrectButtonFrom3(std::vector<std::shared_ptr<GameObject>> &room_objects);
	static std::shared_ptr<GameObject> calcCorrectButtonFrom4(std::vector<std::shared_ptr<GameObject>> &room_objects);
	static std::shared_ptr<GameObject> calcCorrectButtonFrom5(std::vector<std::shared_ptr<GameObject>> &room_objects);
	static std::shared_ptr<GameObject> calcCorrectButtonFrom6(std::vector<std::shared_ptr<GameObject>> &room_objects);

	static std::shared_ptr<GameObject> findButton(std::vector<std::shared_ptr<GameObject>> buttons, int id);
	static std::shared_ptr<GameObject> findButtonByColor(std::vector<std::shared_ptr<GameObject>> buttons, engine::Color c);

	static engine::Color randomButtonColor();

};
