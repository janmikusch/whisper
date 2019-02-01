#include "stdafx.h"
#include "LabyrinthCreator.h"
#include "RandomNumber.h"
#include "WorldBuilder.h"
#include "RigidbodyComponent.h"
#include "WaterComponent.h"

void LabyrinthCreator::createObjectsForLabyrinthRoom(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	auto name = getRandomLabyrinthName();
	WorldBuilder::loadTextures(name);
	auto objects = WorldBuilder::loadWorld(name,sf::Vector2f{0,0});


	auto water = GameObjectCreator::getInstance().createWaterForLavaRiddle(sf::Vector2f{ 0,0 });
	room_objects.push_back(water);

	for(auto it:objects)
	{
		room_objects.push_back(it);

		if(it->getName()=="buttonForLavaRiddle")
		{
			it->getComponent<Rigidbody>()->addObserver(*water->getComponent<WaterComponent>());
		}
	}

}

std::string LabyrinthCreator::getRandomLabyrinthName()
{	
	int nr = engine::Random::getIntBetween(0, 7);

	switch (nr)
	{
	case 1:
		return "lava_map_1.tmx";
		break;
	case 2:
		return "lava_map_2.tmx";
		break;
	case 3:
		return "lava_map_3.tmx";
		break;
	case 4:
		return "lava_map_4.tmx";
		break;
	case 5:
		return "lava_map_5.tmx";
		break;
	case 6:
		return "lava_map_6.tmx";
		break;
	case 7:
		return "lava_map_7.tmx";
		break;
	default:
		return "lava_map_8.tmx";
	}
}
