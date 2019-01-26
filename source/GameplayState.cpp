#include "stdafx.h"
#include <iostream>
#include "GameplayState.h"
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "TextureManager.h"
#include "LayerComponent.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"
#include "TextGuiComponent.h"
#include "FontManager.h"
#include "window.h"

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

	sf::Text text = sf::Text("Press ESC to quit", FontManager::getInstance().getFont("arial"));
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);

	auto window = engine::Window::getInstance().getWindow();
	auto position = sf::Vector2f(window->getSize().x / 2 - text.getString().getSize()*text.getCharacterSize() / 4, window->getSize().y / 2);
	text.setPosition(position);
	std::shared_ptr<GameObject> uiObject = std::make_shared<GameObject>(position, "menu");
	uiObject->addComponent(std::make_shared <TextGuiComponent>(uiObject, Layer::FOREGROUND, text));

	objManager.add(uiObject);

	objManager.applyChanges();

	for (auto it : objManager.getList())
	{
		it->init();
	}
}

void GameplayState::exit()
{
	GameObjectManager& objManager = GameObjectManager::getInstance();
	
	objManager.clear();
}
