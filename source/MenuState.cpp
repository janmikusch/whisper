#include "stdafx.h"
#include "MenuState.h"
#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "InputManager.h"
#include "Layer.h"
#include "TextGuiComponent.h"
#include <SFML/Graphics/Font.hpp>
#include "GameObjectCreator.h"
#include "GameObjectManager.h"
#include "window.h"
#include "FontManager.h"

MenuState::MenuState(StateType type):State(type)
{
}

State::StateType MenuState::update(const float fDeltaTimeSeconds)
{
	GameObjectManager& objManager = GameObjectManager::getInstance();
	InputManager& inputManager = InputManager::getInstance();

	if (inputManager.isKeyDown("StartGame", 0))
	{
		return StateType::STATE_GAMEPLAY;
	}

	for (std::shared_ptr<GameObject> o : objManager.getList())
	{
		if (o != nullptr)
			o->update(fDeltaTimeSeconds);
	}
	return m_type;
}

void MenuState::draw()
{
	GameObjectManager& objManager = GameObjectManager::getInstance();

	for (std::shared_ptr<GameObject> o : GameObjectManager::getInstance().getList())
	{
		if (o != nullptr)
			o->draw();
	}
}

void MenuState::init()
{
	GameObjectManager& objManager = GameObjectManager::getInstance();

	sf::Text text = sf::Text("Press SPACE to start", FontManager::getInstance().getFont("arial"));
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

void MenuState::exit()
{
	GameObjectManager& objManager = GameObjectManager::getInstance();
	objManager.clear();
}
