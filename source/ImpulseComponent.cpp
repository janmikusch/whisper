#include "stdafx.h"
#include "ScoreComponent.h"
#include "RenderManager.h"
#include "window.h"
#include "ImpulseComponent.h"
#include "GameStateManager.h"
#include "InputManager.h"

ImpulseComponent::ImpulseComponent(std::shared_ptr<GameObject> parent) :
	Component(parent)
{
}

void ImpulseComponent::update(const float fDeltaTimeSeconds)
{
	
}

void ImpulseComponent::draw()
{

}

void ImpulseComponent::init()
{
}

void ImpulseComponent::onNotify(const GameObject& collidedWith, const GameObject& ball, engine::GameEvent* event)
{
	if (&this->getGameObject() == &collidedWith)
	{
		std::shared_ptr<Rigidbody> r = std::make_shared<GameObject>(ball)->getComponent<Rigidbody>();

		float randomOffsetX = (std::rand() % 5) - 1.0f;

		r->setVelocity(sf::Vector2f(randomOffsetX, -5.0f));
	}
}