#include "stdafx.h"
#include "ButtonComponent.h"
#include <iostream>
#include "window.h"
#include "RoomManager.h"
#include "EventBus.h"
#include "ButtonForEnemyRiddleComponent.h"
#include "EnemyMoveComponent.h"

ButtonForEnemyRiddleComponent::ButtonForEnemyRiddleComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& texture, engine::Color c, int id) :
	ButtonComponent(parent, layer, texture, c, id)
{
	m_buttonPressed.setTexture(texture);
	m_buttonReleased.setTexture(texture);

	m_buttonReleased.setTextureRect(sf::IntRect(0, 0, 64, 64));
	m_buttonPressed.setTextureRect(sf::IntRect(64, 0, 64, 64));

	m_currentState = m_buttonReleased;
}


void ButtonForEnemyRiddleComponent::onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> gameEvent)
{
	ButtonComponent::onNotify(collidedWith, gameEvent);
	auto cge = std::static_pointer_cast<engine::CollisionGameEvent>(gameEvent);

	if (cge != nullptr && cge->type == engine::CollisionGameEvent::CollisionType::EXIT)
	{
		for (auto o : RoomManager::getInstance().getCurrentRoomObjects())
		{
			if (o->getName() == "enemy")
				o->getComponent<EnemyMoveComponent>()->setFightingState(true);
		}
	}
}
