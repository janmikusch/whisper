#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameObjectCreator.h"
#include "SpriteComponent.h"
#include "LayerComponent.h"
#include "TextGuiComponent.h"
#include "window.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"
#include "BoundingBoxComponent.h"
#include "TextureManager.h"
#include "AnimationComponent.h"
#include "CharacterMoveComponent.h"
#include "FontManager.h"
#include "CharacterAreaComponent.h"
#include "DoorComponent.h"

GameObjectCreator& GameObjectCreator::getInstance()
{
	static GameObjectCreator instance;
	return instance;
}

void GameObjectCreator::init()
{

}


std::shared_ptr<GameObject> GameObjectCreator::createMap(sf::Vector2f position, std::map<std::string, std::vector<std::shared_ptr<sf::Sprite>>> layers)
{
	std::shared_ptr<GameObject> layer = std::make_shared<GameObject>(position, "basicRoom");

	for (auto it : layers)
	{
		Layer currentLayer = StringToLayer::getLayer(it.first);
		auto component_ptr = std::make_shared<LayerComponent>(layer, currentLayer);
		component_ptr->setAllSprites(it.second);
		layer->addComponent(component_ptr);
	}

	return layer;
}



std::shared_ptr<GameObject> GameObjectCreator::createStaticCollider(sf::FloatRect& aabb, sf::Vector2f position)
{
	std::shared_ptr<GameObject> staticCollider = std::make_shared<GameObject>(position, "staticCollider");

	auto rigidbody = std::make_shared<Rigidbody>(staticCollider, 0, false);
	auto collider = std::make_shared<ColliderComponent>(staticCollider, aabb, false);
	staticCollider->addComponent(rigidbody);
	staticCollider->addComponent(collider);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(staticCollider, aabb);
	staticCollider->addComponent(boundingbox);
#endif
	return  staticCollider;
}


std::shared_ptr<GameObject> GameObjectCreator::createCharacter(sf::FloatRect& aabb, int id, sf::Vector2f position)
{
	std::shared_ptr<GameObject> character = std::make_shared<GameObject>(position, "character");

	TextureManager::getInstance().loadTexture("char_animation.png");
	sf::Texture& texture = TextureManager::getInstance().getTexture("char_animation.png");

	auto animComp = std::make_shared<AnimationComponent>(character, Layer::MIDDLE1);

	character->addComponent(animComp);
	character->addComponent(std::make_shared<CharacterMoveComponent>(character, id));

	Animation walkingAnimationDown;
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));

	animComp->addAnimation(walkingAnimationDown, "down");

	Animation walkingAnimationLeft;
	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));

	animComp->addAnimation(walkingAnimationLeft, "left");


	Animation walkingAnimationRight;
	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));

	animComp->addAnimation(walkingAnimationRight, "right");


	Animation walkingAnimationUp;
	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));

	animComp->addAnimation(walkingAnimationUp, "up");

	animComp->setAnimation("down");

	auto rigidbody = std::make_shared<Rigidbody>(character, 1, false, true);
	auto collider = std::make_shared<ColliderComponent>(character, aabb, false);
	character->addComponent(rigidbody);
	character->addComponent(collider);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(character, aabb);
	character->addComponent(boundingbox);
#endif



	return character;
}

std::shared_ptr<GameObject> GameObjectCreator::createCharacterArea(sf::FloatRect& aabb, int id, sf::Vector2f position)
{
	std::shared_ptr<GameObject> area = std::make_shared<GameObject>(position, "area");

	auto rigidbody = std::make_shared<Rigidbody>(area, 0, false);
	auto collider = std::make_shared<ColliderComponent>(area, aabb, true);
	auto areaComp = std::make_shared<CharacterAreaComponent>(area, id);


	area->addComponent(rigidbody);
	area->addComponent(collider);
	area->addComponent(areaComp);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(area, aabb);
	area->addComponent(boundingbox);
#endif
	return  area;
}

std::shared_ptr<GameObject> GameObjectCreator::createDoor(Room::Direction dir, sf::Vector2f position)
{
	std::shared_ptr<GameObject> door = std::make_shared<GameObject>();

	std::shared_ptr<DoorComponent> doorComp;

	switch (dir) { 
	case Room::TOP:
	{
		TextureManager::getInstance().loadTexture("gate_top.png");
		sf::Texture& gateTex = TextureManager::getInstance().getTexture("gate_top.png");
		TextureManager::getInstance().loadTexture("door_top.png");
		sf::Texture& doorTexRed = TextureManager::getInstance().getTexture("door_top.png");
		TextureManager::getInstance().loadTexture("door_top_green.png");
		sf::Texture& doorTexGreen = TextureManager::getInstance().getTexture("door_top_green.png");

		doorComp = std::make_shared<DoorComponent>(door, BACKGROUND3, gateTex, doorTexRed, doorTexGreen, dir);

		door->setPosition(position + sf::Vector2f{ 384, 0 });
	}
		break;
	case Room::RIGHT:
	{
		TextureManager::getInstance().loadTexture("gate_right.png");
		sf::Texture& gateTex = TextureManager::getInstance().getTexture("gate_right.png");
		TextureManager::getInstance().loadTexture("door_right.png");
		sf::Texture& doorTexRed = TextureManager::getInstance().getTexture("door_right.png");
		TextureManager::getInstance().loadTexture("door_right_green.png");
		sf::Texture& doorTexGreen = TextureManager::getInstance().getTexture("door_right_green.png");

		doorComp = std::make_shared<DoorComponent>(door, BACKGROUND3, gateTex, doorTexRed, doorTexGreen, dir);

		door->setPosition(position + sf::Vector2f{ 832, 256 });
	}
		break;
	case Room::BOTTOM:
	{
		TextureManager::getInstance().loadTexture("gate_bottom.png");
		sf::Texture& gateTex = TextureManager::getInstance().getTexture("gate_bottom.png");
		TextureManager::getInstance().loadTexture("door_bottom.png");
		sf::Texture& doorTexRed = TextureManager::getInstance().getTexture("door_bottom.png");
		TextureManager::getInstance().loadTexture("door_bottom_green.png");
		sf::Texture& doorTexGreen = TextureManager::getInstance().getTexture("door_bottom_green.png");

		doorComp = std::make_shared<DoorComponent>(door, BACKGROUND3, gateTex, doorTexRed, doorTexGreen, dir);

		door->setPosition(position + sf::Vector2f{ 384, 576});
	}
		break;
	case Room::LEFT:
	{
		TextureManager::getInstance().loadTexture("gate_left.png");
		sf::Texture& gateTex = TextureManager::getInstance().getTexture("gate_left.png");
		TextureManager::getInstance().loadTexture("door_left.png");
		sf::Texture& doorTexRed = TextureManager::getInstance().getTexture("door_left.png");
		TextureManager::getInstance().loadTexture("door_left_green.png");
		sf::Texture& doorTexGreen = TextureManager::getInstance().getTexture("door_left_green.png");

		doorComp = std::make_shared<DoorComponent>(door, BACKGROUND3, gateTex, doorTexRed,doorTexGreen, dir);

		door->setPosition(position + sf::Vector2f{ 0, 256 });
	}
		break;
	}

	door->addComponent(doorComp);

	return door;
}
