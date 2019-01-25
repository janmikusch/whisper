#include "stdafx.h"
#include "InputManager.h"
#include <SFML/System/Err.hpp>

InputManager& InputManager::getInstance()
{
	static InputManager m_instance;
	return m_instance;
}

bool InputManager::isKeyDown(sf::Keyboard::Key keyCode)
{
	bool pressed = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keyCode));
	bool wasPressed = m_pressedLastFrame.find(keyCode) != m_pressedLastFrame.end() && m_pressedLastFrame[keyCode];

	m_pressedLastFrame[keyCode] = pressed;

	return (pressed && !wasPressed);
}

bool InputManager::isKeyUp(sf::Keyboard::Key keyCode)
{
	bool pressed = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keyCode));
	bool wasPressed = m_pressedLastFrame.find(keyCode) != m_pressedLastFrame.end() && m_pressedLastFrame[keyCode];

	m_pressedLastFrame[keyCode] = pressed;

	return (!pressed && wasPressed);
}

bool InputManager::isKeyPressed(sf::Keyboard::Key keyCode)
{
	return sf::Keyboard::isKeyPressed(keyCode);
}

bool InputManager::isKeyReleased(sf::Keyboard::Key keyCode)
{
	return !sf::Keyboard::isKeyPressed(keyCode);
}


bool InputManager::isKeyDown(std::string action, int playerIdx)
{
	if (!itemExist(action, playerIdx))
		return false;
	return isKeyDown(m_keyMap[playerIdx][action]);
}

bool InputManager::isKeyUp(std::string action, int playerIdx)
{
	if (!itemExist(action, playerIdx))
		return false;
	return isKeyUp(m_keyMap[playerIdx][action]);
}

bool InputManager::isKeyPressed(std::string action, int playerIdx)
{
	if (!itemExist(action, playerIdx))
		return false;
	return isKeyPressed(m_keyMap[playerIdx][action]);
}

bool InputManager::isKeyReleased(std::string action, int playerIdx)
{
	if (!itemExist(action, playerIdx))
		return true;
	return isKeyReleased(m_keyMap[playerIdx][action]);
}

void InputManager::bind(std::string name, sf::Keyboard::Key keyCode, int playerIdx)
{
	m_keyMap[playerIdx].insert_or_assign(name,keyCode);
}

void InputManager::unbind(std::string name, int playerIdx)
{
	auto item = m_keyMap[playerIdx].find(name);
	if(item != m_keyMap[playerIdx].end())
	{
		m_keyMap[playerIdx].erase(item);
	}
}


InputManager::InputManager()
{
	m_keyMap.push_back(std::map<std::string, sf::Keyboard::Key>());
	m_keyMap.push_back(std::map<std::string, sf::Keyboard::Key>());
	m_keyMap.push_back(std::map<std::string, sf::Keyboard::Key>());
	m_keyMap.push_back(std::map<std::string, sf::Keyboard::Key>());
}

bool InputManager::itemExist(std::string name, int playerIdx)
{
	bool exists = m_keyMap[playerIdx].find(name) != m_keyMap[playerIdx].end();
	if(!exists)
	{
		sf::err() << "key " + name + " is not bound" << std::endl;
	}

	return exists;
}
