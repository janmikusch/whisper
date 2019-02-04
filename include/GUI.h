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
		void update(const float fDeltaTimeSeconds);

		void onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent) override;

		tgui::Gui& getGui();

		void setxDisplacement(float xDisplace);
	private:
		GUI(std::shared_ptr<sf::RenderWindow> window);
		tgui::Gui m_gui;
		tgui::Theme m_theme;

		void createMenuGui();
		void createGameplayGui();

		int m_hearts = 3;
		float m_xDisplace;

		bool inMenu = true;
		bool inCredits = false;
		bool inPauseMenu = false;
		bool inGameOverMenu = false;
		bool inGameCompleteSceen = false;

		const float timer_max = 420;
		float timer = 0;
	};
}
