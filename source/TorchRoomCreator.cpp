#include "stdafx.h"
#include "TorchRoomCreator.h"
#include "RandomNumber.h"
#include "window.h"
#include "GameObjectCreator.h"

void TorchRoomCreator::createObjectsForTorchRoom(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	createTorches(room_objects);
	createAnwerObject(room_objects);
}

void TorchRoomCreator::createTorches(std::vector<std::shared_ptr<GameObject>>& room_objects)
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

		std::shared_ptr<GameObject> button = GameObjectCreator::getInstance().createToggleTorch(positionWithOffset, randomTorchColor());

		if (buttonPosition.x >= borderSize + (rangeX / 4) * 3)
		{
			buttonPosition.x = borderSize;
			buttonPosition.y += rangeY / 3;
		}

		room_objects.push_back(button);
	}
}

void TorchRoomCreator::createAnwerObject(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
}

engine::Color TorchRoomCreator::randomTorchColor()
{
	int i = engine::Random::getIntBetween(1, 6);
	return static_cast<engine::Color>(i);
}
