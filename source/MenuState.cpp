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
#include "GUI.h"

MenuState::MenuState(StateType type):State(type)
{
}

State::StateType MenuState::update(const float fDeltaTimeSeconds)
{
	GameObjectManager& objManager = GameObjectManager::getInstance();
	InputManager& inputManager = InputManager::getInstance();


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

	engine::GUI::getInstance().init(m_type);

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
