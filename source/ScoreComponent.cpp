#include "stdafx.h"
#include "ScoreComponent.h"
#include "RenderManager.h"
#include "window.h"
#include "ScoreManager.h"
#include "GameEvent.h"

ScoreComponent::ScoreComponent(std::shared_ptr<GameObject> parent) :
	Component(parent)
{
}

void ScoreComponent::update(const float fDeltaTimeSeconds)
{
	
}

void ScoreComponent::draw()
{

}

void ScoreComponent::init()
{
}

void ScoreComponent::onNotify(const GameObject& collidedWith, const GameObject& ball, engine::GameEvent* event)
{
	auto ev = static_cast<engine::CollisionGameEvent*>(event);
	if(ev == nullptr)
		return;

	if(ev->type != ev->ENTER)
		return;

	if (&this->getGameObject() == &collidedWith)
	{
		ScoreManager::getInstance().addScore(1);
	}
}