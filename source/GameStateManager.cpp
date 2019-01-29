#include "stdafx.h"
#include "GameStateManager.h"
#include <SFML/Graphics.hpp>
#include "RenderManager.h"
#include "GameplayState.h"

void GameStateManager::update(const float fDeltaTimeSeconds)
{
	// handle State Changes

	State::StateType new_state = m_states[m_currentState]->update(fDeltaTimeSeconds);

	if (new_state != m_currentState)
	{
		m_states[m_currentState]->exit();
		setState(new_state);
	}
}

void GameStateManager::draw()
{
	m_states[m_currentState]->draw();
	engine::RenderManager::getInstance().renderAll();
	engine::RenderManager::getInstance().clear();
}

void GameStateManager::setState(State::StateType state)
{
	if (m_states.find(state) == m_states.end())
	{
		sf::err() << "State not found" << std::endl;
	}

	m_currentState = state;
	m_states[m_currentState]->init();
}

void GameStateManager::addState(State::StateType stateType, std::shared_ptr<State> state)
{
	m_states.insert_or_assign(stateType, state);
}


void GameStateManager::onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent)
{
	if(type == engine::EventType::GAMESTART)
	{
		m_states[m_currentState]->exit();
		setState(State::STATE_GAMEPLAY);
	}
	else if(type == engine::EventType::GAMEQUIT)
	{
		m_states[m_currentState]->exit();
		setState(State::STATE_MENU);
	}
	else if (type == engine::EventType::GAMECONTINUE || type == engine::EventType::GAMEOVER)
	{
		std::static_pointer_cast<GameplayState>(m_states[State::STATE_GAMEPLAY])->pause(false);
	}
}
