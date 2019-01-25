#include "stdafx.h"
#include "Game.h"
#include "MenuState.h"
#include "GameplayState.h"
#include "window.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "SFML/System/Err.hpp"
#include <fstream>
#include "AudioManager.h"
#include "FontManager.h"


void Game::run()
{
	if (!init())
		return;

	try
	{
		while (m_window->isOpen())
		{
			sf::Event event;
			while (m_window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_window->close();
				}
			}

			static sf::Clock clock;
			sf::Time deltaTime = clock.restart();
			const float fDeltaTimeSeconds = deltaTime.asSeconds();

			update(fDeltaTimeSeconds);
			draw();
		}
	}
	catch (std::exception ex)
	{
		sf::err() << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "unknown error occured!" << std::endl;
		std::cout << "have a look at the log file" << std::endl;
	}

	shutdown();
}

bool Game::init()
{
	m_frameClock.restart();

	m_window = std::make_shared<sf::RenderWindow>();
	engine::Window::getInstance().setWindow(m_window);

	m_window->create(sf::VideoMode(m_width, m_height), m_gameName);
	m_window->setFramerateLimit(60);

	std::shared_ptr<State> menuState = std::make_shared<MenuState>(State::StateType::STATE_MENU);
	std::shared_ptr<State> gameplayState = std::make_shared<GameplayState>(State::StateType::STATE_GAMEPLAY);

	m_gameStateManager.addState(State::StateType::STATE_MENU,menuState);
	m_gameStateManager.addState(State::StateType::STATE_GAMEPLAY,gameplayState);

	AudioManager& sm = AudioManager::getInstance();

	sm.loadMusicFromAudioXml();
	sm.loadSoundsFromAudioXml();
	sm.init();

	FontManager::getInstance().init();


	GameObjectCreator::getInstance().init();


	m_gameStateManager.setState(State::STATE_MENU);


	WorldBuilder::loadTextures("background.tmx");

	//create input controll
	{
		InputManager::getInstance().bind("FlipperLeft", sf::Keyboard::Key::Left, 0);
		InputManager::getInstance().bind("FlipperRight", sf::Keyboard::Key::Right, 0);
		InputManager::getInstance().bind("MoveLeft", sf::Keyboard::Key::A, 0);
		InputManager::getInstance().bind("MoveUp", sf::Keyboard::Key::W, 0);
		InputManager::getInstance().bind("MoveRight", sf::Keyboard::Key::D, 0);
		InputManager::getInstance().bind("MoveDown", sf::Keyboard::Key::S, 0);
		InputManager::getInstance().bind("EndGame", sf::Keyboard::Key::Escape, 0);
		InputManager::getInstance().bind("StartGame", sf::Keyboard::Key::Space, 0);
		InputManager::getInstance().bind("CreateBall", sf::Keyboard::Key::N, 0);
		InputManager::getInstance().bind("RemoveBall", sf::Keyboard::Key::M, 0);
		InputManager::getInstance().bind("Toggle1", sf::Keyboard::Key::Num1, 0);
		InputManager::getInstance().bind("Toggle2", sf::Keyboard::Key::Num2, 0);
	}

	
	//sm.playSound("testSound");
	//sm.setMusic("testMusic");


	return true;
}

void Game::update(const float fDeltaTimeSeconds)
{
	m_gameStateManager.update(fDeltaTimeSeconds);
}

void Game::shutdown()
{
}

void Game::draw()
{
	m_window->clear();
	m_gameStateManager.draw();
	m_window->display();
}

void Game::writeLogToFile()
{
	std::ofstream file("sfml-log.txt");
	std::streambuf* previous = sf::err().rdbuf(file.rdbuf());
}