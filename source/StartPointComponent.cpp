#include "stdafx.h"
#include "ScoreComponent.h"
#include "RenderManager.h"
#include "window.h"
#include "StartPointComponent.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "RandomNumber.h"

StartPointComponent::StartPointComponent(std::shared_ptr<GameObject> parent) :
	Component(parent)
{
}

void StartPointComponent::update(const float fDeltaTimeSeconds)
{
	
}

void StartPointComponent::draw()
{

}

void StartPointComponent::init()
{
}

void StartPointComponent::onNotify(const GameObject& collidedWith, const GameObject& ball, engine::GameEvent* event)
{
	InputManager& im = InputManager::getInstance();

	if (im.isKeyPressed("StartGame", 0))
	{
		if (&this->getGameObject() == &collidedWith)
		{
			std::shared_ptr<Rigidbody> r = std::make_shared<GameObject>(ball)->getComponent<Rigidbody>();
			sf::Vector2f vec (0.0f, -10.0f);
			vec.x = engine::Random::getFloatBetween(-3.0f, 3.0f);
			
			r->setVelocity(vec);
		}
	}
}