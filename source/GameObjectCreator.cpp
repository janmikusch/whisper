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
	std::shared_ptr<GameObject> layer = std::make_shared<GameObject>(position, "map");

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

	auto animComp = std::make_shared<AnimationComponent>(character, Layer::PLAYER);

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
