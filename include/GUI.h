#pragma once
#include "stdafx.h"
#include <TGUI/TGUI.hpp>
#include "GameplayState.h"
#include "EventObserver.h"


namespace engine
{
	class GUI : public EventObserver
	{
	public:
		static GUI& getInstance();
		void init();
		void init(GameplayState::StateType type);
		void draw();

		void onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent) override;

		tgui::Gui& getGui();
	private:
		GUI(std::shared_ptr<sf::RenderWindow> window);
		tgui::Gui m_gui;
		tgui::Theme m_theme;

		void createMenuGui();
		void createGameplayGui();
	};
}
