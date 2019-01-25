#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameObjectCreator.h"
#include "SpriteComponent.h"
#include "BallInputComponent.h"
#include "FlipperRightInputComponent.h"
#include "FlipperLeftInputComponent.h"
#include "CameraComponent.h"
#include "LayerComponent.h"
#include "TextGuiComponent.h"
#include "window.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"
#include "BoundingBoxComponent.h"
#include "TextureManager.h"
#include "BallGenerateComponent.h"
#include "ScoreManager.h"
#include "ScoreComponent.h"
#include "GameOverComponent.h"
#include "StartPointComponent.h"
#include "ImpulseComponent.h"
#include "AnimationComponent.h"
#include "CharacterMoveComponent.h"
#include "FontManager.h"
#include "CharacterAreaComponent.h"
#include "CoinComponent.h"

GameObjectCreator& GameObjectCreator::getInstance()
{
	static GameObjectCreator instance;
	return instance;
}

std::shared_ptr<GameObject> GameObjectCreator::createBackground(sf::Vector2f position)
{
	std::shared_ptr<GameObject> background = std::make_shared<GameObject>(position,"background");

	std::string textureSrc = "pinball_background.jpg";

	TextureManager::getInstance().loadTexture(textureSrc);
	sf::Texture& texture = TextureManager::getInstance().getTexture(textureSrc);


	background->addComponent(std::make_shared<SpriteComponent>(background, Layer::BACKGROUND,texture));
	background->setScale(sf::Vector2f(800.0f / 855, 600.0f / 645));
	return background;
}

std::shared_ptr<GameObject> GameObjectCreator::createBall(sf::Vector2f position, std::string textureSrc, sf::FloatRect& aabb)
{
	std::shared_ptr<GameObject> ball = std::make_shared<GameObject>(position,"ball");

	TextureManager::getInstance().loadTexture(textureSrc);
	sf::Texture& texture = TextureManager::getInstance().getTexture(textureSrc);

	ball->addComponent(std::make_shared<SpriteComponent>(ball,Layer::PLAYER,texture));

	

	ball->setScale(sf::Vector2f(0.5f, 0.5f));

	ball->addComponent(std::make_shared<BallInputComponent>(ball));
	ball->addComponent(std::make_shared<Rigidbody>(ball,5, true, false));
	ball->addComponent(std::make_shared<ColliderComponent>(ball, aabb));
	ball->addComponent(std::make_shared<BoundingboxComponent>(ball, aabb));


	return ball;
}

std::shared_ptr<GameObject> GameObjectCreator::createRightFlipper(sf::Vector2f position )
{
	sf::Image i;
	i.create(50, 10, sf::Color(255, 255, 255));

	sf::Texture t;
	t.loadFromImage(i);

	sf::FloatRect aabb = sf::FloatRect(position.x, position.y, 50, 10);

	std::shared_ptr<GameObject> rightFlipper = std::make_shared<GameObject>(position,"rightFlipper");
	rightFlipper->addComponent(std::make_shared<SpriteComponent>(rightFlipper, Layer::FOREGROUND, t));
	rightFlipper->addComponent(std::make_shared<FlipperRightInputComponent>(rightFlipper));
	rightFlipper->addComponent(std::make_shared<ImpulseComponent>(rightFlipper));
	rightFlipper->getComponent<FlipperRightInputComponent>()->init();

	return rightFlipper;
}

std::shared_ptr<GameObject> GameObjectCreator::createLeftFlipper(sf::Vector2f position)
{		
	sf::Image i;
	i.create(50, 10, sf::Color(255, 255, 255));

	sf::Texture t;
	t.loadFromImage(i);

	std::shared_ptr<GameObject> leftFlipper = std::make_shared<GameObject>(position,"leftFlipper");
	leftFlipper->addComponent(std::make_shared<SpriteComponent>(leftFlipper, Layer::FOREGROUND, t));
	leftFlipper->addComponent(std::make_shared<FlipperLeftInputComponent>(leftFlipper));

	return  leftFlipper;
}

std::shared_ptr<GameObject> GameObjectCreator::createCamera(sf::Vector2f position)
{
	std::shared_ptr<GameObject> camera = std::make_shared<GameObject>(position,"camera");
	camera->addComponent(std::make_shared<CameraComponent>(camera));


	return camera;
}

std::shared_ptr<GameObject> GameObjectCreator::createMap(sf::Vector2f position, std::map<std::string,std::vector<std::shared_ptr<sf::Sprite>>> layers)
{
	std::shared_ptr<GameObject> layer = std::make_shared<GameObject>(position,"map");
	
	for (auto it : layers)
	{
		Layer currentLayer = StringToLayer::getLayer(it.first);
		auto component_ptr = std::make_shared<LayerComponent>(layer, currentLayer);
		component_ptr->setAllSprites(it.second);
		layer->addComponent(component_ptr);
	}
	
	return layer;
}

std::shared_ptr<GameObject> GameObjectCreator::createMenuStartText(sf::Vector2f position)
{
	sf::Text text = sf::Text("Press SPACE to start", FontManager::getInstance().getFont("arial"));
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	if (position == sf::Vector2f())
	{
		auto window = engine::Window::getInstance().getWindow();
		position = sf::Vector2f(window->getSize().x / 2 - text.getString().getSize()*text.getCharacterSize() / 4, window->getSize().y / 2);
	}
	text.setPosition(position);
	std::shared_ptr<GameObject> uiObject = std::make_shared<GameObject>(position,"menu");
	uiObject->addComponent(std::make_shared <TextGuiComponent>(uiObject, Layer::FOREGROUND, text));
	return uiObject;
}

std::shared_ptr<GameObject> GameObjectCreator::createStaticCollider(sf::FloatRect& aabb, sf::Vector2f position)
{
	std::shared_ptr<GameObject> staticCollider = std::make_shared<GameObject>(position,"staticCollider");

	auto rigidbody = std::make_shared<Rigidbody>(staticCollider, 0, false);
	auto collider = std::make_shared<ColliderComponent>(staticCollider, aabb, false);
	staticCollider->addComponent(rigidbody);
	staticCollider->addComponent(collider);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(staticCollider,aabb);
	staticCollider->addComponent(boundingbox);
#endif
	return  staticCollider;
}

std::shared_ptr<GameObject> GameObjectCreator::createFlipperCollider(sf::FloatRect& aabb, sf::Vector2f position)
{
	std::shared_ptr<GameObject> flipperCollider = std::make_shared<GameObject>(position, "flipperCollider");

	auto rigidbody = std::make_shared<Rigidbody>(flipperCollider, 0, false);
	auto collider = std::make_shared<ColliderComponent>(flipperCollider, aabb, true);
	auto impulse = std::make_shared<ImpulseComponent>(flipperCollider);
	flipperCollider->addComponent(rigidbody);
	flipperCollider->addComponent(collider);
	flipperCollider->addComponent(impulse);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(flipperCollider, aabb);
	flipperCollider->addComponent(boundingbox);
#endif
	return  flipperCollider;
}

std::shared_ptr<GameObject> GameObjectCreator::createMouse(sf::FloatRect& aabb, sf::Vector2f position)
{
	std::string filename = "mouse.png";
	TextureManager::getInstance().loadTexture(filename);

	std::shared_ptr<GameObject> mouse = std::make_shared<GameObject>(position,"mouse");

	auto spriteComp = std::make_shared<SpriteComponent>(mouse, Layer::OBJECTS, TextureManager::getInstance().getTexture(filename));
	spriteComp->scale(sf::Vector2f(0.5f,0.5f));
	auto rigidbody = std::make_shared<Rigidbody>(mouse, 0, false);
	auto collider = std::make_shared<ColliderComponent>(mouse, aabb, true);
	auto score = std::make_shared<ScoreComponent>(mouse);
	mouse->addComponent(rigidbody);
	mouse->addComponent(collider);
	mouse->addComponent((spriteComp));
	mouse->addComponent(score);


#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(mouse,aabb);
	mouse->addComponent(boundingbox);
#endif
	return  mouse;
}

//TODO
std::shared_ptr<GameObject> GameObjectCreator::createStartPoint(sf::Vector2f position, std::string textureSrc, sf::FloatRect& aabb)
{
	std::shared_ptr<GameObject> trigger = std::make_shared<GameObject>(position,"start");

	auto rigidbody = std::make_shared<Rigidbody>(trigger, 0, false);
	auto collider = std::make_shared<ColliderComponent>(trigger, aabb, true);
	auto creator = std::make_shared<BallGenerateComponent>(trigger, textureSrc, aabb);
	auto startpoint = std::make_shared<StartPointComponent>(trigger);
	trigger->addComponent(rigidbody);
	trigger->addComponent(collider);
	trigger->addComponent(creator);
	trigger->addComponent(startpoint);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(trigger, aabb);
	trigger->addComponent(boundingbox);
#endif
	return trigger;
}

//TODO
std::shared_ptr<GameObject> GameObjectCreator::createGameOverTrigger(sf::FloatRect& aabb, sf::Vector2f position)
{
	std::shared_ptr<GameObject> trigger = std::make_shared<GameObject>(position,"end");

	auto rigidbody = std::make_shared<Rigidbody>(trigger, 0, false);
	auto collider = std::make_shared<ColliderComponent>(trigger, aabb, true);
	auto gameOver = std::make_shared<GameOverComponent>(trigger);
	trigger->addComponent(rigidbody);
	trigger->addComponent(collider);
	trigger->addComponent(gameOver);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(trigger, aabb);
	trigger->addComponent(boundingbox);
#endif
	return trigger;
}

std::shared_ptr<GameObject> GameObjectCreator::createScore (sf::Vector2f position)
{
	sf::Text text = sf::Text(std::to_string(ScoreManager::getInstance().getScore()), FontManager::getInstance().getFont("arial"));
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	if (position == sf::Vector2f())
	{
		auto window = engine::Window::getInstance().getWindow();
		position = sf::Vector2f(0,0);
	}
	text.setPosition(position);
	std::shared_ptr<GameObject> uiObject = std::make_shared<GameObject>(position, "score");
	uiObject->addComponent(std::make_shared <TextGuiComponent>(uiObject, Layer::FOREGROUND, text));
	return uiObject;
}

std::shared_ptr<GameObject> GameObjectCreator::createCharacter(sf::FloatRect& aabb, int id,sf::Vector2f position)
{
	std::shared_ptr<GameObject> character = std::make_shared<GameObject>(position, "character");

	TextureManager::getInstance().loadTexture("char_animation.png");
	sf::Texture& texture = TextureManager::getInstance().getTexture("char_animation.png");

	auto animComp = std::make_shared<AnimationComponent>(character, Layer::PLAYER);

	character->addComponent(animComp);
	character->addComponent(std::make_shared<CharacterMoveComponent>(character,id));

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

	auto rigidbody = std::make_shared<Rigidbody>(character, 1, false,true);
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
	auto areaComp = std::make_shared<CharacterAreaComponent>(area,id);
	auto coinComp = std::make_shared<CoinComponent>(area, Layer::OBJECTS, aabb);


	area->addComponent(rigidbody);
	area->addComponent(collider);
	area->addComponent(areaComp);
	area->addComponent(coinComp);

#ifdef _DEBUG
	auto boundingbox = std::make_shared <BoundingboxComponent>(area, aabb);
	area->addComponent(boundingbox);
#endif
	return  area;
}

void GameObjectCreator::init()
{

}



/// use Animation
	/*ball->addComponent(std::make_shared<AnimationComponent>(ball,Layer::PLAYER));

	TextureManager::getInstance().loadTexture("animation.png");
	texture = TextureManager::getInstance().getTexture("animation.png");

	Animation walkingAnimationDown;
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));

	ball->getComponent<AnimationComponent>()->addAnimation(walkingAnimationDown, "down");
	ball->getComponent<AnimationComponent>()->setAnimation("down");*/
