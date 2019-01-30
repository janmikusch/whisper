#include "stdafx.h"
#include "Color.h"
#include "GameObject.h"
#include "ButtonRoomCreator.h"
#include "ButtonComponent.h"
#include "RandomNumber.h"
#include "GameObjectCreator.h"
#include "window.h"
#include "ButtonRoomComponent.h"
#include "RigidbodyComponent.h"
#include "RoomManager.h"

void ButtonRoomCreator::createObjectsForButtonRoom(std::vector<std::shared_ptr<GameObject>>& room_objects, int i)
{
	createButtons(room_objects, i);
	createTorches(room_objects);
	createButtonRoomChecker(room_objects, i);
}

void ButtonRoomCreator::createButtons(std::vector<std::shared_ptr<GameObject>>& room_objects, int i)
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

void ButtonRoomCreator::createTorches(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	engine::Color c = engine::Color::RED;

	int randomMin = 0;
	int randomMax = 8;

	int random = engine::Random::getIntBetween(randomMin, randomMax);
	sf::Vector2u winSize = engine::Window::getInstance().getWindow()->getSize();
	int torchWidth = 64;


	if (random == randomMax)
	{
		std::shared_ptr<GameObject> flame = GameObjectCreator::getInstance().createTorch(sf::Vector2f(winSize.x / 3 - torchWidth / 2, 40), c);
		room_objects.push_back(flame);
	}

	random = engine::Random::getIntBetween(randomMin, randomMax);

	if (random == randomMax)
	{
		std::shared_ptr<GameObject> flame = GameObjectCreator::getInstance().createTorch(sf::Vector2f((winSize.x / 3) * 2 - torchWidth / 2, 40), c);
		room_objects.push_back(flame);
	}

	random = engine::Random::getIntBetween(randomMin, randomMax);

	if (random == randomMax)
	{
		std::shared_ptr<GameObject> flame = GameObjectCreator::getInstance().createTorch(sf::Vector2f(winSize.x / 3 + torchWidth / 2, winSize.y - 40), c);
		flame->setRotation(180.0f);
		room_objects.push_back(flame);
	}

	random = engine::Random::getIntBetween(randomMin, randomMax);

	if (random == randomMax)
	{
		std::shared_ptr<GameObject> flame = GameObjectCreator::getInstance().createTorch(sf::Vector2f((winSize.x / 3) * 2 + torchWidth / 2, winSize.y - 40), c);
		flame->setRotation(180.0f);
		room_objects.push_back(flame);
	}

}

void ButtonRoomCreator::createButtonRoomChecker(std::vector<std::shared_ptr<GameObject>>& room_objects, int i)
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

	for (auto it : room_objects)
	{
		if (it->getName() != "button")
			continue;
		it->getComponent<Rigidbody>()->addObserver(*brComp);
	}

	room_objects.push_back(brc);
}

void ButtonRoomCreator::create3Buttons(std::vector<std::shared_ptr<GameObject>>& room_objects)
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

		std::shared_ptr<GameObject> button = GameObjectCreator::getInstance().createButton(positionWithOffset, randomButtonColor(), i);



		room_objects.push_back(button);
	}
}

void ButtonRoomCreator::create4Buttons(std::vector<std::shared_ptr<GameObject>>& room_objects)
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

		std::shared_ptr<GameObject> button = GameObjectCreator::getInstance().createButton(positionWithOffset, randomButtonColor(), i);

		if (buttonPosition.x >= borderSize + (rangeX / 3) * 2)
		{
			buttonPosition.x = borderSize;
			buttonPosition.y += rangeY / 3;
		}

		room_objects.push_back(button);
	}
}

void ButtonRoomCreator::create5Buttons(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	create4Buttons(room_objects);

	sf::Vector2u winSize = engine::Window::getInstance().getWindow()->getSize();

	int borderSize = 120;
	int buttonWidth = 64;

	float rangeX = winSize.x - 2 * borderSize;
	float rangeY = winSize.y - 2 * borderSize;

	sf::Vector2f position = sf::Vector2f(rangeX * 0.68 - buttonWidth / 2, rangeY * 0.75 - buttonWidth / 2);


	std::shared_ptr<GameObject> button = GameObjectCreator::getInstance().createButton(position, randomButtonColor(), 4);
	room_objects.push_back(button);

}

void ButtonRoomCreator::create6Buttons(std::vector<std::shared_ptr<GameObject>>& room_objects)
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

		std::shared_ptr<GameObject> button = GameObjectCreator::getInstance().createButton(positionWithOffset, randomButtonColor(), i);

		if (buttonPosition.x >= borderSize + (rangeX / 4) * 3)
		{
			buttonPosition.x = borderSize;
			buttonPosition.y += rangeY / 3;
		}

		room_objects.push_back(button);
	}
}

std::shared_ptr<GameObject> ButtonRoomCreator::calcCorrectButtonFrom3(std::vector<std::shared_ptr<GameObject>>& room_objects)
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

std::shared_ptr<GameObject> ButtonRoomCreator::calcCorrectButtonFrom4(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	return std::shared_ptr<GameObject>();
}

std::shared_ptr<GameObject> ButtonRoomCreator::calcCorrectButtonFrom5(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	return std::shared_ptr<GameObject>();
}

std::shared_ptr<GameObject> ButtonRoomCreator::calcCorrectButtonFrom6(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	return std::shared_ptr<GameObject>();
}

std::shared_ptr<GameObject> ButtonRoomCreator::findButton(std::vector<std::shared_ptr<GameObject>> buttons, int id)
{
	for (auto b : buttons)
	{
		if (b->getComponent<ButtonComponent>()->getId() == id)
			return b;
	}

	return nullptr;
}


engine::Color ButtonRoomCreator::randomButtonColor()
{
	int i = engine::Random::getIntBetween(0, 5);
	return static_cast<engine::Color>(i);
}