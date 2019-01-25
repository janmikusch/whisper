#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameStateManager.h"
#include "GameObject.h"

class Game
{
public:
	Game() = default;
	bool init();
	void update(const float fDeltaTimeSeconds);
	void shutdown();
	void run();
	void draw();
private:
	void writeLogToFile();

	std::shared_ptr<sf::RenderWindow> m_window;
	sf::Clock m_frameClock;
	GameStateManager m_gameStateManager;
	const std::string m_gameName = "BasicEngine";
	const int m_height = 600;
	const int m_width = 800;
};
