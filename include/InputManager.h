#pragma once
#include "stdafx.h"
#include <string>
#include <map>
#include <vector>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

class InputManager
{
public:
	enum StickDirection {NONE,LEFT, RIGHT, UP, DOWN};
	enum JoystickButton {A,B,X,Y,LB,RB,BACK,START};

	static InputManager& getInstance();
	bool isKeyDown(sf::Keyboard::Key keyCode);
	bool isKeyUp(sf::Keyboard::Key keyCode);
	bool isKeyPressed(sf::Keyboard::Key keyCode);
	bool isKeyReleased(sf::Keyboard::Key keyCode);
	
	bool isKeyDown(std::string action, int playerIdx);
	bool isKeyUp(std::string action, int playerIdx);
	bool isKeyPressed(std::string action, int playerIdx);
	bool isKeyReleased(std::string action, int playerIdx);
	
	void bind(std::string name, sf::Keyboard::Key keyCode, int playerIdx);
	void unbind(std::string name, int playerIdx);

	StickDirection getLeftJoystickAxis();
	StickDirection getLeftJoystickDownAxis();
	bool isJoystickButtonDown(JoystickButton b);
	bool isJoystickButtonPressed(JoystickButton b);
	bool itemExist(std::string name, int playerIdx);

private:
	InputManager();
	~InputManager() = default;
	InputManager(const InputManager& p) = delete;
	InputManager& operator=(InputManager const&) = delete;

	std::vector<std::map<std::string, sf::Keyboard::Key>> m_keyMap;
	std::map<JoystickButton, bool> m_pressedLastJSButton;

	std::map<int, bool> m_pressedLastFrame;

	StickDirection lastDirection;


	int buttonToId(JoystickButton b);
};

