#include "stdafx.h"
#include "TorchRoomCreator.h"
#include "RandomNumber.h"
#include "window.h"
#include "GameObjectCreator.h"
#include <immintrin.h>
#include "TorchAnimationComponent.h"

void TorchRoomCreator::createObjectsForTorchRoom(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	createTorches(room_objects);
	createAnwerObject(room_objects);
}

int TorchRoomCreator::getValueFromColor(engine::Color c)
{
	switch (c) {
	case engine::BLUE: 
		return 7;
		break;
	case engine::GREEN: 
		return 3;
		break;
	case engine::RED: 
		return 5;
		break;
	case engine::WHITE: 
		return -6;
		break;
	case engine::YELLOW: 
		return -4;
		break;
	case engine::VIOLET: 
		return -2;
		break;
	}
	return 0;
}

void TorchRoomCreator::createTorches(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	sf::Vector2f winSize{ 960, 704 };

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
	int answer1 = calcAnswer(room_objects);
	int answer2 = calcAnswer(room_objects);
	int answer3 = calcAnswer(room_objects);
	int finalAnwer = 3;

	if (answer1 != 0)
		finalAnwer = answer1;
	else if (answer2 != 0)
		finalAnwer = answer2;

	auto obj = GameObjectCreator::getInstance().createToggleAnswerObject(sf::Vector2f{700,130}, finalAnwer);
	
	room_objects.push_back(obj);
}

int TorchRoomCreator::calcAnswer(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	int answer = 0;
	for (auto it : room_objects)
	{
		if (it->getName() != "toggleTorch")
		{
			continue;
		}
		int colVal = getValueFromColor(it->getComponent<TorchAnimationComponent>()->getFlameColor());
		int onOff = engine::Random::getIntBetween(0, 10);
		if (onOff > 5)
		{
			answer += colVal;
		}
	}
	return answer;
}

engine::Color TorchRoomCreator::randomTorchColor()
{
	int i = engine::Random::getIntBetween(1, 6);
	return static_cast<engine::Color>(i);
}
