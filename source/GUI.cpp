#include "stdafx.h"
#include "GUI.h"
#include "window.h"
#include "FontManager.h"
#include "Game.h"
#include "TextureManager.h"
#include "RoomManager.h"

using namespace engine;

GUI& engine::GUI::getInstance()
{
	static GUI instance(engine::Window::getInstance().getWindow());
	return  instance;
}

void GUI::init()
{
	m_theme = tgui::Theme{ "../assets/TGUI/Black.txt" };
	tgui::Theme::setDefault(&m_theme);
	//register to EventBus
	//TODO
	EventBus::getInstance().addObserver(engine::EventType::GAMEPAUSE, this);
	EventBus::getInstance().addObserver(engine::EventType::GAMEOVER, this);
	EventBus::getInstance().addObserver(engine::EventType::DAMAGETAKEN, this);
	EventBus::getInstance().addObserver(engine::EventType::ROOMUNLOCKED, this);
	EventBus::getInstance().addObserver(engine::EventType::GAMECOMPLETE, this);
}

void GUI::init(GameplayState::StateType type)
{
	switch (type) 
	{
	case State::STATE_MENU:
		createMenuGui();
		break;
	case State::STATE_GAMEPLAY:
		createGameplayGui();
		m_hearts = 3;
		break;
	}
}

void GUI::draw()
{
	m_gui.draw();
}

void GUI::onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent)
{
	//TODO
	if(type == EventType::GAMEPAUSE)
	{
		m_gui.get("pausemenu")->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(10));
	}
	if (type == EventType::GAMEOVER)
	{
		m_gui.get("gameover")->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(10));
	}
	if (type == EventType::GAMECOMPLETE)
	{
		m_gui.get("gamecomplete")->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(10));
	}
	if (type == engine::EventType::DAMAGETAKEN)
	{
		m_hearts--;
		if(m_hearts == 2)
		{
			m_gui.get("heart3")->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(50));
		}
		if (m_hearts == 1)
		{
			m_gui.get("heart2")->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(50));
		}
		if (m_hearts == 0)
		{
			m_gui.get("heart1")->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(50));
		}
	}
	if(type == engine::EventType::ROOMUNLOCKED)
	{
		int count = RoomManager::getInstance().countNotCompleted();
		std::string text = "Rooms reft: ";
		m_gui.get<tgui::Label>("roomsleft")->setText(text + std::to_string(count));
	}

}

tgui::Gui& GUI::getGui()
{
	return m_gui;
}

GUI::GUI(std::shared_ptr<sf::RenderWindow> window):m_gui(*window)
{
}

void GUI::createMenuGui()
{
	m_gui.removeAllWidgets();

	tgui::Panel::Ptr panel = tgui::Panel::create();
	panel->getRenderer()->setBackgroundColor(tgui::Color::White);

	//CREDITS
	tgui::ChildWindow::Ptr credits = tgui::ChildWindow::create("",tgui::ChildWindow::TitleButton::None);
	credits->hideWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(1));
	credits->setSize("100%", "100%");
	credits->setPosition("0%","0%");
	credits->setPositionLocked(true);

	tgui::Button::Ptr creditsClose = tgui::Button::create("Back");
	creditsClose->setTextSize(30);
	creditsClose->setPosition({ "98% - width", "2%" });
	creditsClose->connect("pressed", [&]() { m_gui.get("CreditScreen")->hideWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(100)); });
	credits->add(creditsClose);

	{
		tgui::Label::Ptr title = tgui::Label::create("Credits");
		title->setTextSize(100);
		credits->add(title);

		tgui::VerticalLayout::Ptr layout = tgui::VerticalLayout::create();
		layout->setPosition("10", "30%");
		layout->setSize("70%", "60%");
		credits->add(layout);

		tgui::Label::Ptr fhs = tgui::Label::create("FH Salzburg\nMultimedia Technology\nMMP2a");
		fhs->setTextSize(30);
		layout->add(fhs);

		tgui::Label::Ptr devs = tgui::Label::create("Developer:\nJan Mikusch\nRobin Unger");
		devs->setTextSize(30);
		layout->add(devs);

		TextureManager::getInstance().loadTexture("Logo_FHS_transparent_bg_white.png");
		tgui::Picture::Ptr logo = tgui::Picture::create(TextureManager::getInstance().getTexture("Logo_FHS_transparent_bg_white.png"));
		logo->setPosition({ "90% - width", "80% - height" });
		credits->add(logo);

	}


	//ENDCREDITS



	tgui::Label::Ptr label = tgui::Label::create("Wisper");
	label->setTextSize(150);
	label->setInheritedFont(FontManager::getInstance().getFont("Neverwinter"));
	label->setPosition({ "50% - width / 2", "10%" });


	tgui::VerticalLayout::Ptr layout = tgui::VerticalLayout::create();
	layout->setInheritedFont(FontManager::getInstance().getFont("Arial"));
	layout->setSize("60%%", "50%");
	layout->setPosition("20%", "40%");


	tgui::Button::Ptr startButton = tgui::Button::create("Start");
	startButton->setTextSize(50);
	startButton->connect("pressed", [&]() { EventBus::getInstance().notify(engine::GAMESTART, make_shared<GameEvent>()); });

	tgui::Button::Ptr creditsButton = tgui::Button::create("Credits");
	creditsButton->setTextSize(50);
	creditsButton->connect("pressed", [&]() { m_gui.get("CreditScreen")->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(100)); });

	tgui::Button::Ptr quitButton = tgui::Button::create("Quit");	
	quitButton->setTextSize(50);
	quitButton->connect("pressed", [&]() { engine::Window::getInstance().getWindow()->close(); });

	m_gui.add(panel);
	m_gui.add(credits, "CreditScreen");
	panel->add(label);
	panel->add(layout);
	layout->add(startButton);
	layout->add(creditsButton);
	layout->add(quitButton);

	layout->insertSpace(1, 0.15f);
	layout->insertSpace(3, 0.15f);

}

void GUI::createGameplayGui()
{
	m_gui.removeAllWidgets();

	//pausemenue
	{
		tgui::Panel::Ptr pausemenu = tgui::Panel::create();
		pausemenu->hideWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(1));
		pausemenu->setSize("60%", "40%");
		pausemenu->setPosition("20%", "30%");
		auto bgcolor = tgui::Color(8, 43, 43, 255);
		pausemenu->getRenderer()->setBackgroundColor(bgcolor);
		m_gui.add(pausemenu, "pausemenu");


		tgui::VerticalLayout::Ptr layout = tgui::VerticalLayout::create();
		layout->setInheritedFont(FontManager::getInstance().getFont("Arial"));
		layout->setSize("60%", "50%");
		layout->setPosition("20%", "40%");
		pausemenu->add(layout);

		tgui::Label::Ptr title = tgui::Label::create("Pause");
		title->setTextSize(50);
		title->setPosition({ "50% - width / 2", "10%" });
		pausemenu->add(title);

		tgui::Button::Ptr btn_continue = tgui::Button::create("Continue");
		btn_continue->setTextSize(30);
		btn_continue->connect("pressed", [&]()
			{
				m_gui.get("pausemenu")->hideWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(10));
				EventBus::getInstance().notify(engine::GAMECONTINUE, make_shared<GameEvent>());
			});
		layout->add(btn_continue);

		tgui::Button::Ptr btn_quit = tgui::Button::create("Give Up");
		btn_quit->setTextSize(30);
		btn_quit->connect("pressed", [&]() { EventBus::getInstance().notify(engine::GAMEQUIT, make_shared<GameEvent>()); });
		layout->add(btn_quit);

		layout->insertSpace(1, 0.3f);
	}

	//GAME OVER
	{
		tgui::Panel::Ptr gameovermenu = tgui::Panel::create();
		gameovermenu->hideWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(1));
		gameovermenu->setSize("60%", "40%");
		gameovermenu->setPosition("20%", "30%");
		auto bgcolor = tgui::Color(8, 43, 43, 255);
		gameovermenu->getRenderer()->setBackgroundColor(bgcolor);
		m_gui.add(gameovermenu, "gameover");


		tgui::VerticalLayout::Ptr layout = tgui::VerticalLayout::create();
		layout->setInheritedFont(FontManager::getInstance().getFont("Arial"));
		layout->setSize("60%", "50%");
		layout->setPosition("20%", "40%");
		gameovermenu->add(layout);

		tgui::Label::Ptr title = tgui::Label::create("Game Over");
		title->setTextSize(50);
		title->setPosition({ "50% - width / 2", "10%" });
		gameovermenu->add(title);


		tgui::Button::Ptr btn_quit = tgui::Button::create("Back to Menu");
		btn_quit->setTextSize(30);
		btn_quit->connect("pressed", [&]() { EventBus::getInstance().notify(engine::GAMEQUIT, make_shared<GameEvent>()); });
		layout->add(btn_quit);

		layout->insertSpace(1, 0.3f);
	}

	//GAME OVER
	{
		tgui::Panel::Ptr gamecomplete = tgui::Panel::create();
		gamecomplete->hideWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(1));
		gamecomplete->setSize("60%", "40%");
		gamecomplete->setPosition("20%", "30%");
		auto bgcolor = tgui::Color(8, 43, 43, 255);
		gamecomplete->getRenderer()->setBackgroundColor(bgcolor);
		m_gui.add(gamecomplete, "gamecomplete");


		tgui::VerticalLayout::Ptr layout = tgui::VerticalLayout::create();
		layout->setInheritedFont(FontManager::getInstance().getFont("Arial"));
		layout->setSize("60%", "50%");
		layout->setPosition("20%", "40%");
		gamecomplete->add(layout);

		tgui::Label::Ptr title = tgui::Label::create("Game Completed \n Your Rock!");
		title->setTextSize(30);
		title->setPosition({ "50% - width / 2", "10%" });
		gamecomplete->add(title);


		tgui::Button::Ptr btn_quit = tgui::Button::create("Back to Menu");
		btn_quit->setTextSize(30);
		btn_quit->connect("pressed", [&]() { EventBus::getInstance().notify(engine::GAMEQUIT, make_shared<GameEvent>()); });
		layout->add(btn_quit);

		layout->insertSpace(1, 0.3f);
	}

	TextureManager::getInstance().loadTexture("heart.png");
	sf::Texture& heartTexture = TextureManager::getInstance().getTexture("heart.png");
	tgui::Picture::Ptr heart = tgui::Picture::create(heartTexture);
	heart->setPosition({ "5%", "1%" });
	m_gui.add(heart,"heart1");

	TextureManager::getInstance().loadTexture("heart.png");
	tgui::Picture::Ptr heart2 = tgui::Picture::create(heartTexture);
	heart2->setPosition({ "5% + width * 1", "1%" });
	m_gui.add(heart2, "heart2");

	TextureManager::getInstance().loadTexture("heart.png");
	tgui::Picture::Ptr heart3 = tgui::Picture::create(heartTexture);
	heart3->setPosition({ "5% + width * 2", "1%" });
	m_gui.add(heart3, "heart3");

	tgui::Label::Ptr rooms = tgui::Label::create("Rooms reft: 5");
	rooms->setTextSize(20);
	rooms->setPosition({ "95% - width", "1%" });
	m_gui.add(rooms, "roomsleft");
}
