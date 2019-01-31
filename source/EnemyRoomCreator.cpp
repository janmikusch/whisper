#include "stdafx.h"
#include "EnemyRoomCreator.h"
#include "GameObjectManager.h"
#include "GameObjectCreator.h"


void EnemyRoomCreator::createObjectsForEnemyRoom(std::vector<std::shared_ptr<GameObject>>& room_objects)
{
	std::shared_ptr<GameObject> target;

	for (auto o : GameObjectManager::getInstance().getList())
	{
		if (o->getName() == "hero")
			target = o;
	}

	sf::FloatRect rectW = sf::FloatRect(130, 100, 120, 128);
	std::shared_ptr<GameObject> enemyWater = GameObjectCreator::getInstance().createEnemy(rectW, engine::Element::WATER, target, 1, sf::Vector2f(rectW.left, rectW.top));
	room_objects.push_back(enemyWater);

	sf::FloatRect rectF = sf::FloatRect(710, 100, 120, 128);
	std::shared_ptr<GameObject> enemyFire = GameObjectCreator::getInstance().createEnemy(rectF, engine::Element::FIRE, target, 2, sf::Vector2f(rectF.left, rectF.top));
	room_objects.push_back(enemyFire);

	sf::FloatRect rectA = sf::FloatRect(130, 410, 120, 128);
	std::shared_ptr<GameObject> enemyAir = GameObjectCreator::getInstance().createEnemy(rectA, engine::Element::AIR, target, 3, sf::Vector2f(rectA.left, rectA.top));
	room_objects.push_back(enemyAir);

	sf::FloatRect rectE = sf::FloatRect(710, 410, 120, 128);
	std::shared_ptr<GameObject> enemyEarth = GameObjectCreator::getInstance().createEnemy(rectE, engine::Element::EARTH, target, 4, sf::Vector2f(rectE.left, rectE.top));
	room_objects.push_back(enemyEarth);
}
