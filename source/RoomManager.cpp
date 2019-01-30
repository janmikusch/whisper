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

	createObjectsForButtonRoom(roomObjects_00, 3);//engine::Random::getIntBetween(3,6));

	createTorches(roomObjects_00);

	room_00->setRoomObjects(roomObjects_00);
	room_01->setRoomObjects(roomObjects_01);
	room_02->setRoomObjects(roomObjects_02);
	room_10->setRoomObjects(roomObjects_10);
	room_11->setRoomObjects(roomObjects_11);
	room_12->setRoomObjects(roomObjects_12);
}

void RoomManager::init()
{
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
		newPos.y = 512 - 8;
		break;
	case Room::RIGHT:
		newPos.x = 128 + 8;
		newPos.y = 320;
		break;
	case Room::BOTTOM:
		newPos.x = 448;
		newPos.y = 128 + 8;
		break;
	case Room::LEFT:
		newPos.x = 768 - 8;
		newPos.y = 320;
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

RoomManager::RoomManager():EventObserver()
{
	EventBus::getInstance().addObserver(engine::DOORENTER, this);
	EventBus::getInstance().addObserver(engine::DAMAGETAKEN, this);
	EventBus::getInstance().addObserver(engine::ROOMUNLOCKED, this);

}

void RoomManager::createObjectsForButtonRoom(std::vector<std::shared_ptr<GameObject>>& room_objects, int i)
{
	createButtons(room_objects, i);
	createTorches(room_objects);
	createButtonRoomChecker(room_objects, i);
}

void RoomManager::createButtons(std::vector<std::shared_ptr<GameObject>>& room_objects, int i)
{
	switch (i)
	{
	case 3:
		create3Buttons(room_objects);
		break;
	case 4:
		create4Buttons(room_objects);
		break;
	case 5:
		create5Buttons(room_objects);
		break;
	case 6:
		create6Buttons(room_objects);
		break;
	default:
		sf::err() << "Method not allowed";
		return;
	}
}

void RoomManager::createTorches(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	engine::Color c = engine::Color::BLACK;

	int randomMin = 0;
	int randomMax = 8;

	int random = engine::Random::getIntBetween(randomMin, randomMax);
	sf::Vector2u winSize = engine::Window::getInstance().getWindow()->getSize();
	int torchWidth = 64;


	if (random == randomMax)
	{
		std::shared_ptr<GameObject> flame = GameObjectCreator::getInstance().createTorch(sf::Vector2f(winSize.x/3-torchWidth/2, 40), c);
		room_objects.push_back(flame);
	}

	random = engine::Random::getIntBetween(randomMin, randomMax);
	
	if (random == randomMax)
	{
		std::shared_ptr<GameObject> flame = GameObjectCreator::getInstance().createTorch(sf::Vector2f((winSize.x / 3)*2 - torchWidth / 2, 40), c);
		room_objects.push_back(flame);
	}

	random = engine::Random::getIntBetween(randomMin, randomMax);

	if (random == randomMax)
	{
		std::shared_ptr<GameObject> flame = GameObjectCreator::getInstance().createTorch(sf::Vector2f(winSize.x / 3 + torchWidth/2, winSize.y - 40), c);
		flame->setRotation(180.0f);
		room_objects.push_back(flame);
	}

	random = engine::Random::getIntBetween(randomMin, randomMax);

	if (random == randomMax)
	{
		std::shared_ptr<GameObject> flame = GameObjectCreator::getInstance().createTorch(sf::Vector2f((winSize.x / 3)*2 + torchWidth / 2, winSize.y - 40), c);
		flame->setRotation(180.0f);
		room_objects.push_back(flame);
	}

}

void RoomManager::createButtonRoomChecker(std::vector<std::shared_ptr<GameObject>>& room_objects, int i)
{
	std::shared_ptr<GameObject> correctButton = nullptr;
	switch (i)
	{
	case 3:
		correctButton = calcCorrectButtonFrom3(room_objects);
		break;
	case 4:
		correctButton = calcCorrectButtonFrom4(room_objects);
		break;
	case 5:
		correctButton = calcCorrectButtonFrom5(room_objects);
		break;
	case 6:
		correctButton = calcCorrectButtonFrom6(room_objects);
		break;
	default:
		sf::err() << "wrong int input " << std::endl;
		return;
	}

	auto brc = GameObjectCreator::getInstance().createButtonRoomChecker(sf::Vector2f{ 0,0 }, correctButton);

	auto brComp = brc->getComponent<ButtonRoomComponent>();

	for(auto it:room_objects)
	{
		if(it->getName() != "button")
			continue;
		it->getComponent<Rigidbody>()->addObserver(*brComp);
	}

	room_objects.push_back(brc);
}

void RoomManager::create3Buttons(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	sf::Vector2u winSize = engine::Window::getInstance().getWindow()->getSize();

	int borderSize = 120;
	int buttonWidth = 64;

	float rangeX = winSize.x - 2 * borderSize;
	float rangeY = winSize.y - 2 * borderSize;

	sf::Vector2f buttonPosition = sf::Vector2f(borderSize, borderSize + rangeY / 2);

	for (int i = 0; i < 3; i++)
	{
		buttonPosition.x += rangeX / 4;

		sf::Vector2f positionWithOffset = sf::Vector2f(buttonPosition.x - buttonWidth / 2, buttonPosition.y - buttonWidth / 2);

		std::shared_ptr<GameObject> button = GameObjectCreator::getInstance().createButton(positionWithOffset, randomColor(), i);



		room_objects.push_back(button);
	}
}

void RoomManager::create4Buttons(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	sf::Vector2u winSize = engine::Window::getInstance().getWindow()->getSize();

	int borderSize = 120;
	int buttonWidth = 64;

	float rangeX = winSize.x - 2 * borderSize;
	float rangeY = winSize.y - 2 * borderSize;

	sf::Vector2f buttonPosition = sf::Vector2f(borderSize, borderSize + rangeY / 3);

	for (int i = 0; i < 4; i++)
	{
		buttonPosition.x += rangeX / 3;

		sf::Vector2f positionWithOffset = sf::Vector2f(buttonPosition.x - buttonWidth / 2, buttonPosition.y - buttonWidth / 2);

		std::shared_ptr<GameObject> button = GameObjectCreator::getInstance().createButton(positionWithOffset, randomColor(), i);

		if (buttonPosition.x >= borderSize + (rangeX / 3) * 2)
		{
			buttonPosition.x = borderSize;
			buttonPosition.y += rangeY / 3;
		}

		room_objects.push_back(button);
	}
}

void RoomManager::create5Buttons(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	create4Buttons(room_objects);

	sf::Vector2u winSize = engine::Window::getInstance().getWindow()->getSize();

	int borderSize = 120;
	int buttonWidth = 64;

	float rangeX = winSize.x - 2 * borderSize;
	float rangeY = winSize.y - 2 * borderSize;

	sf::Vector2f position = sf::Vector2f(rangeX * 0.68  - buttonWidth / 2, rangeY * 0.75 - buttonWidth / 2);


	std::shared_ptr<GameObject> button = GameObjectCreator::getInstance().createButton(position, randomColor(), 4);
	room_objects.push_back(button);

}

void RoomManager::create6Buttons(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	sf::Vector2u winSize = engine::Window::getInstance().getWindow()->getSize();

	int borderSize = 120;
	int buttonWidth = 64;

	float rangeX = winSize.x - 2 * borderSize;
	float rangeY = winSize.y - 2 * borderSize;

	sf::Vector2f buttonPosition = sf::Vector2f(borderSize, borderSize + rangeY / 3);

	for (int i = 0; i < 6; i++)
	{
		buttonPosition.x += rangeX / 4;

		sf::Vector2f positionWithOffset = sf::Vector2f(buttonPosition.x - buttonWidth / 2, buttonPosition.y - buttonWidth / 2);

		std::shared_ptr<GameObject> button = GameObjectCreator::getInstance().createButton(positionWithOffset, randomColor(), i);

		if (buttonPosition.x >= borderSize + (rangeX / 4) * 3)
		{
			buttonPosition.x = borderSize;
			buttonPosition.y += rangeY / 3;
		}

		room_objects.push_back(button);
	}
}

std::shared_ptr<GameObject> RoomManager::calcCorrectButtonFrom3(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	int countBlack = 0;
	int countViolet = 0;
	int countBlue = 0;
	int countRed = 0;
	int countGreen = 0;
	int countWhite = 0;
	int countYellow = 0;

	std::shared_ptr<GameObject> targetButton = nullptr;

	std::vector<std::shared_ptr<GameObject>> buttons;

	for (auto o : room_objects)
	{
		if (o->getName() == "button")
		{
			buttons.push_back(o);
			engine::Color c;

			c = o->getComponent<ButtonComponent>()->getColor();

			switch (c)
			{
			case engine::Color::BLACK:
				countBlack++;
				break;
			case engine::Color::BLUE:
				countBlue++;
				break;
			case engine::Color::GREEN:
				countGreen++;
				break;
			case engine::Color::RED:
				countRed++;
				break;
			case engine::Color::WHITE:
				countWhite++;
				break;
			case engine::Color::YELLOW:
				countYellow++;
				break;
			}
		}
	}

	if (countRed == 0)
	{
		targetButton = findButton(buttons, 1);
	}
	else if (findButton(buttons, 2)->getComponent<ButtonComponent>()->getColor() == engine::Color::BLUE)
	{
		targetButton = findButton(buttons, 0);
	}
	else if (countGreen > 1)
	{
		targetButton = findButton(buttons, 2);
	}
	else
	{
		targetButton = findButton(buttons, 0);
	}

	return targetButton;
}

std::shared_ptr<GameObject> RoomManager::calcCorrectButtonFrom4(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	return std::shared_ptr<GameObject>();
}

std::shared_ptr<GameObject> RoomManager::calcCorrectButtonFrom5(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	return std::shared_ptr<GameObject>();
}

std::shared_ptr<GameObject> RoomManager::calcCorrectButtonFrom6(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	return std::shared_ptr<GameObject>();
}

engine::Color RoomManager::randomColor()
{
	int i = engine::Random::getIntBetween(0, 5);
	return static_cast<engine::Color>(i);
}

std::shared_ptr<Room> RoomManager::getRoom(int i)
{
	return m_rooms[i];
}


std::shared_ptr<GameObject> RoomManager::findButton(std::vector<std::shared_ptr<GameObject>> buttons, int id)
{
	for (auto b : buttons)
	{
		if (b->getComponent<ButtonComponent>()->getId() == id)
			return b;
	}

	return nullptr;
}
