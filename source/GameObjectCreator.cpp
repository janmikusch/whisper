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
#include "HeroAnimationComponent.h"
#include "CharacterMoveComponent.h"
#include "FontManager.h"
#include "CharacterAreaComponent.h"
#include "DoorComponent.h"
#include "FadeComponent.h"
#include "ButtonComponent.h"
#include "TorchAnimationComponent.h"
#include "ButtonRoomComponent.h"
#include "TorchRoomSolverComponent.h"
#include "LavaComponent.h"
#include "RandomNumber.h"
#include "ButtonForLavaRiddleComponent.h"
#include "WaterComponent.h"

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
	std::shared_ptr<GameObject> character = std::make_shared<GameObject>(position, "hero");

	TextureManager::getInstance().loadTexture("hero.png");
	sf::Texture& texture = TextureManager::getInstance().getTexture("hero.png");

	std::shared_ptr<AnimationComponent> animComp = std::make_shared<HeroAnimationComponent>(character, Layer::MIDDLE1, 0.1f);

	character->addComponent(animComp);
	character->addComponent(std::make_shared<CharacterMoveComponent>(character, id));

	Animation walkingAnimationUp;
	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(0, 512, 64, 64));
	walkingAnimationUp.addFrame(sf::IntRect(64, 512, 64, 64));
	walkingAnimationUp.addFrame(sf::IntRect(128, 512, 64, 64));
	walkingAnimationUp.addFrame(sf::IntRect(192, 512, 64, 64));
	walkingAnimationUp.addFrame(sf::IntRect(256, 512, 64, 64));
	walkingAnimationUp.addFrame(sf::IntRect(320, 512, 64, 64));
	walkingAnimationUp.addFrame(sf::IntRect(384, 512, 64, 64));
	walkingAnimationUp.addFrame(sf::IntRect(448, 512, 64, 64));
	walkingAnimationUp.addFrame(sf::IntRect(512, 512, 64, 64));
	
	animComp->addAnimation(walkingAnimationUp, "up");

	Animation walkingAnimationLeft;
	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(0, 576, 64, 64));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 576, 64, 64));
	walkingAnimationLeft.addFrame(sf::IntRect(128, 576, 64, 64));
	walkingAnimationLeft.addFrame(sf::IntRect(192, 576, 64, 64));
	walkingAnimationLeft.addFrame(sf::IntRect(256, 576, 64, 64));
	walkingAnimationLeft.addFrame(sf::IntRect(320, 576, 64, 64));
	walkingAnimationLeft.addFrame(sf::IntRect(384, 576, 64, 64));
	walkingAnimationLeft.addFrame(sf::IntRect(448, 576, 64, 64));
	walkingAnimationLeft.addFrame(sf::IntRect(512, 576, 64, 64));

	animComp->addAnimation(walkingAnimationLeft, "left");


	Animation walkingAnimationDown;
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(0, 640, 64, 64));
	walkingAnimationDown.addFrame(sf::IntRect(64, 640, 64, 64));
	walkingAnimationDown.addFrame(sf::IntRect(128, 640, 64, 64));
	walkingAnimationDown.addFrame(sf::IntRect(192, 640, 64, 64));
	walkingAnimationDown.addFrame(sf::IntRect(256, 640, 64, 64));
	walkingAnimationDown.addFrame(sf::IntRect(320, 640, 64, 64));
	walkingAnimationDown.addFrame(sf::IntRect(384, 640, 64, 64));
	walkingAnimationDown.addFrame(sf::IntRect(448, 640, 64, 64));
	walkingAnimationDown.addFrame(sf::IntRect(512, 640, 64, 64));

	animComp->addAnimation(walkingAnimationDown, "down");


	Animation walkingAnimationRight;
	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(0, 704, 64, 64));
	walkingAnimationRight.addFrame(sf::IntRect(64, 704, 64, 64));
	walkingAnimationRight.addFrame(sf::IntRect(128, 704, 64, 64));
	walkingAnimationRight.addFrame(sf::IntRect(192, 704, 64, 64));
	walkingAnimationRight.addFrame(sf::IntRect(256, 704, 64, 64));
	walkingAnimationRight.addFrame(sf::IntRect(320, 704, 64, 64));
	walkingAnimationRight.addFrame(sf::IntRect(384, 704, 64, 64));
	walkingAnimationRight.addFrame(sf::IntRect(448, 704, 64, 64));
	walkingAnimationRight.addFrame(sf::IntRect(512, 704, 64, 64));

	animComp->addAnimation(walkingAnimationRight, "right");


	Animation standingDown;
	standingDown.setSpriteSheet(texture);
	standingDown.addFrame(sf::IntRect(0, 640, 64, 64));

	animComp->addAnimation(standingDown, "standingDown");

	Animation standingUp;
	standingUp.setSpriteSheet(texture);
	standingUp.addFrame(sf::IntRect(0, 512, 64, 64));

	animComp->addAnimation(standingUp, "standingUp");

	Animation standingLeft;
	standingLeft.setSpriteSheet(texture);
	standingLeft.addFrame(sf::IntRect(0, 576, 64, 64));

	animComp->addAnimation(standingLeft, "standingLeft");

	Animation standingRight;
	standingRight.setSpriteSheet(texture);
	standingRight.addFrame(sf::IntRect(0, 704, 64, 64));

	animComp->addAnimation(standingRight, "standingRight");


	Animation fightUp;
	fightUp.setSpriteSheet(texture);
	fightUp.addFrame(sf::IntRect(0, 1408, 192, 192));
	fightUp.addFrame(sf::IntRect(192, 1408, 192, 192));
	fightUp.addFrame(sf::IntRect(384, 1408, 192, 192));
	fightUp.addFrame(sf::IntRect(576, 1408, 192, 192));
	fightUp.addFrame(sf::IntRect(768, 1408, 192, 192));
	fightUp.addFrame(sf::IntRect(960, 1408, 192, 192));
	
	animComp->addAnimation(fightUp, "fightUp");

	Animation fightLeft;
	fightLeft.setSpriteSheet(texture);
	fightLeft.addFrame(sf::IntRect(0, 1600, 192, 192));
	fightLeft.addFrame(sf::IntRect(192, 1600, 192, 192));
	fightLeft.addFrame(sf::IntRect(384, 1600, 192, 192));
	fightLeft.addFrame(sf::IntRect(576, 1600, 192, 192));
	fightLeft.addFrame(sf::IntRect(768, 1600, 192, 192));
	fightLeft.addFrame(sf::IntRect(960, 1600, 192, 192));

	animComp->addAnimation(fightLeft, "fightLeft");

	Animation fightDown;
	fightDown.setSpriteSheet(texture);
	fightDown.addFrame(sf::IntRect(0, 1792, 192, 192));
	fightDown.addFrame(sf::IntRect(192, 1792, 192, 192));
	fightDown.addFrame(sf::IntRect(384, 1792, 192, 192));
	fightDown.addFrame(sf::IntRect(576, 1792, 192, 192));
	fightDown.addFrame(sf::IntRect(768, 1792, 192, 192));
	fightDown.addFrame(sf::IntRect(960, 1792, 192, 192));

	animComp->addAnimation(fightDown, "fightDown");

	Animation fightRight;
	fightRight.setSpriteSheet(texture); 
	fightRight.addFrame(sf::IntRect(0, 1984, 192, 192));
	fightRight.addFrame(sf::IntRect(192, 1984, 192, 192));
	fightRight.addFrame(sf::IntRect(384, 1984, 192, 192));
	fightRight.addFrame(sf::IntRect(576, 1984, 192, 192));
	fightRight.addFrame(sf::IntRect(768, 1984, 192, 192));
	fightRight.addFrame(sf::IntRect(960, 1984, 192, 192));

	animComp->addAnimation(fightRight, "fightRight");

	animComp->setAnimation("standingDown");

	sf::Vector2f displacement(18, 40);

	aabb.height -= 45;
	aabb.width -= 36;


	auto rigidbody = std::make_shared<Rigidbody>(character, 1, false, false);
	auto collider = std::make_shared<ColliderComponent>(character, aabb, false, displacement);
	character->addComponent(rigidbody);
	character->addComponent(collider);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(character, aabb);
	boundingbox->setDisplacement(displacement);
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
	std::string name = ""; 
	switch (dir)
	{
	case Room::TOP: name = "door_top";
		break;
	case Room::RIGHT: name = "door_right";
		break;
	case Room::BOTTOM: name = "door_bottom";
		break;
	case Room::LEFT: name = "door_left";
		break;
	}
	std::shared_ptr<GameObject> door = std::make_shared<GameObject>(position, name);

	std::shared_ptr<DoorComponent> doorComp;
	std::shared_ptr<ColliderComponent> collider;
	std::shared_ptr<Rigidbody> rigidbody = std::make_shared<Rigidbody>(door, 1, false, true);

	sf::FloatRect rect{};
	rect.height = 32;
	rect.width = 32;
	sf::Vector2f displacement{};

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


		rect.left = door->getPosition().x + 80;
		rect.top = door->getPosition().y + 96;
		displacement.x = 80;
		displacement.y = 96;

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


		rect.left = door->getPosition().x;
		rect.top = door->getPosition().y + 80;
		displacement.x = 0;
		displacement.y = 80;
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


		rect.left = door->getPosition().x + 80;
		rect.top = door->getPosition().y;
		displacement.x = 80;
		displacement.y = 0;
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


		rect.left = door->getPosition().x + 96;
		rect.top = door->getPosition().y + 80;
		displacement.x = 96;
		displacement.y = 80;
	}
		break;
	}
	collider = std::make_shared<ColliderComponent>(door, rect, true);

	door->addComponent(doorComp);
	door->addComponent(rigidbody);
	door->addComponent(collider);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(door, rect,Layer::DEBUG_BOUNDINGBOX,displacement);
	door->addComponent(boundingbox);
#endif

	rigidbody->addObserver(*doorComp);

	return door;
}

std::shared_ptr<GameObject> GameObjectCreator::createFade(sf::Vector2f position)
{
	std::shared_ptr<GameObject> fader = std::make_shared<GameObject>(position, "fade");

	fader->addComponent(std::make_shared<FadeComponent>(fader, Layer::FOREGROUND3));
	return fader;
}

std::shared_ptr<GameObject> GameObjectCreator::createButton(sf::Vector2f position, engine::Color c, int id)
{
	sf::FloatRect rect = sf::FloatRect(position, sf::Vector2f(54, 56));
	sf::Vector2f displacement = sf::Vector2f(5, 0);
	sf::Texture *texture = nullptr;

	switch (c)
	{
	case engine::Color::BLACK:
		TextureManager::getInstance().loadTexture("button_black.png");
		texture = &TextureManager::getInstance().getTexture("button_black.png");
		break;
	case engine::Color::BLUE:
		TextureManager::getInstance().loadTexture("button_blue.png");
		texture = &TextureManager::getInstance().getTexture("button_blue.png");
		break;
	case engine::Color::GREEN:
		TextureManager::getInstance().loadTexture("button_green.png");
		texture = &TextureManager::getInstance().getTexture("button_green.png");
		break;
	case engine::Color::RED:
		TextureManager::getInstance().loadTexture("button_red.png");
		texture = &TextureManager::getInstance().getTexture("button_red.png");
		break;
	case engine::Color::YELLOW:
		TextureManager::getInstance().loadTexture("button_yellow.png");
		texture = &TextureManager::getInstance().getTexture("button_yellow.png");
		break;
	case engine::Color::WHITE:
		TextureManager::getInstance().loadTexture("button_white.png");
		texture = &TextureManager::getInstance().getTexture("button_white.png");
		break;
	default:
		sf::err() << "Color not defined";
	}
	
	std::shared_ptr<GameObject> button = std::make_shared<GameObject>(position, "button");

	std::shared_ptr<ColliderComponent> collider = std::make_shared<ColliderComponent>(button, rect, true, displacement);
	std::shared_ptr<Rigidbody> rigidbody = std::make_shared<Rigidbody>(button, 1, false, true);
	std::shared_ptr<ButtonComponent> buttonComp = std::make_shared<ButtonComponent>(button, Layer::BACKGROUND3, *texture, c, id);

	button->addComponent(collider);
	button->addComponent(rigidbody);
	button->addComponent(buttonComp);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(button, rect, Layer::DEBUG_BOUNDINGBOX);
	boundingbox->setDisplacement(displacement);
	button->addComponent(boundingbox);
#endif

	rigidbody->addObserver(*buttonComp);

	return button;
}

std::shared_ptr<GameObject> GameObjectCreator::createTorch(sf::Vector2f position, engine::Color c)
{
	sf::FloatRect rect = sf::FloatRect(position, sf::Vector2f(64, 64));
	sf::Vector2f displacement = sf::Vector2f(0, 0);
	sf::Texture *texture = nullptr;

	switch (c)
	{
	case engine::Color::BLUE:
		TextureManager::getInstance().loadTexture("flame_blue.png");
		texture = &TextureManager::getInstance().getTexture("flame_blue.png");
		break;
	case engine::Color::GREEN:
		TextureManager::getInstance().loadTexture("flame_green.png");
		texture = &TextureManager::getInstance().getTexture("flame_green.png");
		break;
	case engine::Color::RED:
		TextureManager::getInstance().loadTexture("flame_red.png");
		texture = &TextureManager::getInstance().getTexture("flame_red.png");
		break;
	case engine::Color::YELLOW:
		TextureManager::getInstance().loadTexture("flame_yellow.png");
		texture = &TextureManager::getInstance().getTexture("flame_yellow.png");
		break;
	case engine::Color::WHITE:
		TextureManager::getInstance().loadTexture("flame_white.png");
		texture = &TextureManager::getInstance().getTexture("flame_white.png");
		break;
	case engine::Color::VIOLET:
		TextureManager::getInstance().loadTexture("flame_violet.png");
		texture = &TextureManager::getInstance().getTexture("flame_violet.png");
		break;
	default:
		sf::err() << "Color not defined";
	}

	std::shared_ptr<GameObject> torch = std::make_shared<GameObject>(position, "torch");

	TextureManager::getInstance().loadTexture("torch_handle.png");
	sf::Texture &handleTex = TextureManager::getInstance().getTexture("torch_handle.png");

	std::shared_ptr<AnimationComponent> animComp = std::make_shared<TorchAnimationComponent>(torch, Layer::MIDDLE1, handleTex,c, 0.1f);

	torch->addComponent(animComp);

	Animation flameAnimation;
	flameAnimation.setSpriteSheet(*texture);
	flameAnimation.addFrame(sf::IntRect(0, 0, 64, 64));
	flameAnimation.addFrame(sf::IntRect(64, 0, 64, 64));
	flameAnimation.addFrame(sf::IntRect(128, 0, 64, 64));
	flameAnimation.addFrame(sf::IntRect(192, 0, 64, 64));
	flameAnimation.addFrame(sf::IntRect(0, 64, 64, 64));
	flameAnimation.addFrame(sf::IntRect(64, 64, 64, 64));

	animComp->addAnimation(flameAnimation, "flameAnimation");

	animComp->setAnimation("flameAnimation");

	return torch;
}

std::shared_ptr<GameObject> GameObjectCreator::createButtonRoomChecker(sf::Vector2f position,std::shared_ptr<GameObject> correctButton)
{
	std::shared_ptr<GameObject> brc = std::make_shared<GameObject>(position, "buttonRoomChecker");

	auto buttonRoomComponent = std::make_shared<ButtonRoomComponent>(brc);

	buttonRoomComponent->setCorrectButton(correctButton);

	brc->addComponent(buttonRoomComponent);

	return brc;
}

std::shared_ptr<GameObject> GameObjectCreator::createToggleTorch(sf::Vector2f position, engine::Color c)
{
	auto toggleTorch = createTorch(position, c);
	toggleTorch->setName("toggleTorch");

	sf::FloatRect rect = sf::FloatRect(position, sf::Vector2f(64, 64));

	sf::Vector2f displacement(18, 60);

	rect.height -= 45;
	rect.width -= 36;
	
	std::shared_ptr<ColliderComponent> collider = std::make_shared<ColliderComponent>(toggleTorch, rect, false, displacement);
	std::shared_ptr<Rigidbody> rigidbody = std::make_shared<Rigidbody>(toggleTorch, 1, false, true);

	toggleTorch->addComponent(collider);
	toggleTorch->addComponent(rigidbody);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(toggleTorch, rect, Layer::DEBUG_BOUNDINGBOX);
	boundingbox->setDisplacement(displacement);
	toggleTorch->addComponent(boundingbox);
#endif

	return toggleTorch;
}

std::shared_ptr<GameObject> GameObjectCreator::createToggleAnswerObject(sf::Vector2f position, int answer)
{
	std::shared_ptr<GameObject> torchAnswer = std::make_shared<GameObject>(position, "torchAnswer");

	TextureManager::getInstance().loadTexture("answer_background.png");
	sf::Texture& texture = TextureManager::getInstance().getTexture("answer_background.png");

	torchAnswer->addComponent(std::make_shared<TorchRoomSolverComponent>(torchAnswer, answer, texture));


	return torchAnswer;
}

std::shared_ptr<GameObject> GameObjectCreator::createLava(sf::Vector2f position)
{
	std::shared_ptr<GameObject> lava = std::make_shared<GameObject>(position, "lava");

	sf::FloatRect aabb = sf::FloatRect(position, sf::Vector2f(64, 64));

	int randomNr = engine::Random::getIntBetween(0, 6);

	sf::IntRect textureRect;
	textureRect.width = 64;
	textureRect.height = 64;

	switch (randomNr)
	{
	case 0:
		textureRect.left = 0;
		textureRect.top = 0;
		break;
	case 1:
		textureRect.left = 64;
		textureRect.top = 0;
		break;
	case 2:
		textureRect.left = 0;
		textureRect.top = 64;
		break;
	case 3:
		textureRect.left = 64;
		textureRect.top = 64;
		break;
	case 4:
		textureRect.left = 128;
		textureRect.top = 64;
		break;
	case 5:
		textureRect.left = 192;
		textureRect.top = 64;
		break;
	case 6:
		textureRect.left = 256;
		textureRect.top = 64;
		break;
	}

	TextureManager::getInstance().loadTexture("lava_spritesheet.png");
	sf::Texture& texture = TextureManager::getInstance().getTexture("lava_spritesheet.png");

	auto collider = std::make_shared<ColliderComponent>(lava, aabb, true);
	auto rigidbody = std::make_shared<Rigidbody>(lava, 1, false, true);
	auto lavaComp = std::make_shared<LavaComponent>(lava, Layer::BACKGROUND3, texture, textureRect);

	lava->addComponent(collider);
	lava->addComponent(rigidbody);
	lava->addComponent(lavaComp);

	rigidbody->addObserver(*lavaComp);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(lava, aabb, Layer::DEBUG_BOUNDINGBOX);
	lava->addComponent(boundingbox);
#endif

	return lava;
}

std::shared_ptr<GameObject> GameObjectCreator::createButtonForLavaRiddle(sf::Vector2f position)
{
	sf::FloatRect rect = sf::FloatRect(position, sf::Vector2f(54, 56));
	sf::Vector2f displacement = sf::Vector2f(5, 0);

	TextureManager::getInstance().loadTexture("button_green.png");
	sf::Texture& texture = TextureManager::getInstance().getTexture("button_green.png");

	std::shared_ptr<GameObject> button = std::make_shared<GameObject>(position, "buttonForLavaRiddle");

	std::shared_ptr<ColliderComponent> collider = std::make_shared<ColliderComponent>(button, rect, true, displacement);
	std::shared_ptr<Rigidbody> rigidbody = std::make_shared<Rigidbody>(button, 1, false, true);
	std::shared_ptr<ButtonForLavaRiddleComponent> buttonComp = std::make_shared<ButtonForLavaRiddleComponent>(button, Layer::BACKGROUND3, texture, engine::Color::GREEN, 1);

	button->addComponent(collider);
	button->addComponent(rigidbody);
	button->addComponent(buttonComp);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(button, rect, Layer::DEBUG_BOUNDINGBOX);
	boundingbox->setDisplacement(displacement);
	button->addComponent(boundingbox);
#endif

	rigidbody->addObserver(*buttonComp);

	return button;
}

std::shared_ptr<GameObject> GameObjectCreator::createWaterForLavaRiddle(sf::Vector2f position)
{
	TextureManager::getInstance().loadTexture("lava_map_water.png");
	sf::Texture& texture = TextureManager::getInstance().getTexture("lava_map_water.png");

	std::shared_ptr<GameObject> waterObj = std::make_shared<GameObject>(position, "water");

	auto water = std::make_shared<WaterComponent>(waterObj, Layer::BACKGROUND4, texture);

	waterObj->addComponent(water);

	return waterObj;
}
