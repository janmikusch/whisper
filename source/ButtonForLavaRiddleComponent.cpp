#include "stdafx.h"
#include "ButtonComponent.h"
#include <iostream>
#include "window.h"
#include "RoomManager.h"
#include "EventBus.h"
#include "ButtonForLavaRiddleComponent.h"

ButtonForLavaRiddleComponent::ButtonForLavaRiddleComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& texture, engine::Color c, int id) :
	ButtonComponent(parent, layer, texture, c, id)
{
	m_buttonPressed.setTexture(texture);
	m_buttonReleased.setTexture(texture);

	m_buttonReleased.setTextureRect(sf::IntRect(0, 0, 64, 64));
	m_buttonPressed.setTextureRect(sf::IntRect(64, 0, 64, 64));

	m_currentState = m_buttonReleased;
}


void ButtonForLavaRiddleComponent::onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> gameEvent)
{
	ButtonComponent::onNotify(collidedWith, gameEvent);
	auto cge = std::static_pointer_cast<engine::CollisionGameEvent>(gameEvent);

	if (cge != nullptr && cge->type == engine::CollisionGameEvent::CollisionType::ENTER)
	{
		EventBus::getInstance().notify(engine::EventType::ROOMUNLOCKED, std::shared_ptr<engine::GameEvent>());
	}
}
