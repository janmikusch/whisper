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

InputManager::StickDirection InputManager::getLeftJoystickAxis()
{
	if (!sf::Joystick::isConnected(0))
		return NONE;

	float xPos = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float yPos = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

#ifdef _DEBUG
	sf::err() << "X:" << xPos << " Y:" << yPos << std::endl;
#endif

	float max = 100;

	if (xPos < max * -0.5)
		
	{
		lastDirection = StickDirection::LEFT;
		return StickDirection::LEFT;
	}
	else if(xPos > max * 0.5)
	{
		lastDirection = StickDirection::RIGHT;
		return StickDirection::RIGHT;
	}
	else if (yPos < max *  -0.5)
	{
		lastDirection = StickDirection::UP;
		return StickDirection::UP;
	}
	else if (yPos > max * 0.5)
	{
		lastDirection = StickDirection::DOWN;
		return StickDirection::DOWN;
	}
	else
	{
		lastDirection = StickDirection::NONE;
		return StickDirection::NONE;
	}
}

InputManager::StickDirection InputManager::getLeftJoystickDownAxis()
{
	if (!sf::Joystick::isConnected(0))
		return NONE;

	auto last = lastDirection;
	auto now = getLeftJoystickAxis();

	if (last != now)
		return now;
	return NONE;
}

bool InputManager::isJoystickButtonDown(JoystickButton b)
{
	if (!sf::Joystick::isConnected(0))
		return false;

	auto it = m_pressedLastJSButton.find(b);

	bool wasPressed = it != m_pressedLastJSButton.end() && m_pressedLastJSButton[b];
	bool isPressed = isJoystickButtonPressed(b);

	if(wasPressed == false)
	{
		return isPressed;
	}
	return false;
}

bool InputManager::isJoystickButtonPressed(JoystickButton b)
{
	if (!sf::Joystick::isConnected(0))
		return false;

	bool pressed = false;
	switch (b)
	{
	case A:
		pressed = sf::Joystick::isButtonPressed(0,buttonToId(b));
			break;
	case B:
		pressed = sf::Joystick::isButtonPressed(0, buttonToId(b));
		break;
	case X:
		pressed = sf::Joystick::isButtonPressed(0, buttonToId(b));
		break;
	case Y:
		pressed = sf::Joystick::isButtonPressed(0, buttonToId(b));
		break;
	case LB:
		pressed = sf::Joystick::isButtonPressed(0, buttonToId(b));
		break;
	case RB:
		pressed = sf::Joystick::isButtonPressed(0, buttonToId(b));
		break;
	case BACK:
		pressed = sf::Joystick::isButtonPressed(0, buttonToId(b));
		break;
	case START:
		pressed = sf::Joystick::isButtonPressed(0, buttonToId(b));
		break;
	}
	m_pressedLastJSButton[b] = pressed;

	return pressed;
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

int InputManager::buttonToId(JoystickButton b)
{

	switch (b)
	{
	case A:
		return 0;
	case B:
		return 1;
	case X:
		return 2;
	case Y:
		return 3;
	case LB:
		return 4;
	case RB:
		return 5;
	case BACK:
		return 6;
	case START:
		return 7;
	default:
		return false;
	}
}
