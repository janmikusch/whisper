#include "stdafx.h"
#include "ScoreComponent.h"
#include "RenderManager.h"
#include "window.h"
#include "GameOverComponent.h"
#include "GameStateManager.h"

GameOverComponent::GameOverComponent(std::shared_ptr<GameObject> parent) :
	Component(parent)
{
}

void GameOverComponent::update(const float fDeltaTimeSeconds)
{
	
}

void GameOverComponent::draw()
{

}

void GameOverComponent::init()
{
}

void GameOverComponent::onNotify(const GameObject& collidedWith, const GameObject& ball, engine::GameEvent* event)
{
	if (&this->getGameObject() == &collidedWith)
	{
		m_isGameOver = true;
	}
}