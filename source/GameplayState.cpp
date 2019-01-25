#include "stdafx.h"
#include <iostream>
#include "GameplayState.h"
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "CameraComponent.h"
#include "TextureManager.h"
#include "LayerComponent.h"
#include "BallGenerateComponent.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"
#include "ScoreManager.h"
#include "TextGuiComponent.h"
#include "GameOverComponent.h"
#include "FontManager.h"

GameplayState::GameplayState(StateType type) :State(type)
{
}

State::StateType GameplayState::update(const float fDeltaTimeSeconds)
{
	GameObjectManager& objManager = GameObjectManager::getInstance();
	if (InputManager::getInstance().isKeyDown("EndGame",0))
	{
		exit();
		return State::StateType::STATE_MENU;
	}

	for (std::shared_ptr<GameObject> o : objManager.getList())
	{
		if (o->getName() == "score")
		{
			int score = ScoreManager::getInstance().getScore();
			sf::String text = std::to_string(score);
			o->getComponent<TextGuiComponent>()->setTextContent(text);
		}

		if (o->getName() == "end")
		{
			if (o->getComponent<GameOverComponent>()->getGameOver())
			{
				exit();
				return State::StateType::STATE_MENU;
			}
		}

		if(o != nullptr)
			o->update(fDeltaTimeSeconds);
	}


	PhysicsManager::getInstance().findCollisions(objManager.getList());

	objManager.applyChanges();
	return m_type;
}

void GameplayState::draw()
{
	for (std::shared_ptr<GameObject> o : GameObjectManager::getInstance().getList())
	{
		o->draw();
	}
}

void GameplayState::init()
{
	GameObjectManager& objManager = GameObjectManager::getInstance();

	auto gameObjects = WorldBuilder::loadWorld("background.tmx", sf::Vector2f());

	for(auto obj:gameObjects)
	{
		objManager.add(obj);
	}

	std::shared_ptr<GameObject> camera = GameObjectCreator::getInstance().createCamera(sf::Vector2f(0, 0));
	auto camComponent = camera->getComponent<CameraComponent>();
	
	objManager.add(camera);

	objManager.applyChanges();

	for (auto it : objManager.getList())
	{
		it->init();
	}
}

void GameplayState::exit()
{
	GameObjectManager& objManager = GameObjectManager::getInstance();

	for (std::shared_ptr<GameObject> o : objManager.getList())
	{
		if (o->getComponent<CameraComponent>() != nullptr)
		{
			o->getComponent<CameraComponent>()->reset();
		}
	}

	objManager.clear();
	ScoreManager::getInstance().resetScore();
}
