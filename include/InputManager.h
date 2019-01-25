#pragma once
#include "stdafx.h"
#include <string>
#include <map>
#include <vector>
#include <SFML/Window/Keyboard.hpp>

class InputManager
{
	bool itemExist(std::string name, int playerIdx);
public:
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

	std::map<int, bool> m_pressedLastFrame;
private:
	InputManager();
	~InputManager() = default;
	InputManager(const InputManager& p) = delete;
	InputManager& operator=(InputManager const&) = delete;

	std::vector<std::map<std::string, sf::Keyboard::Key>> m_keyMap;

};

