#include "stdafx.h"
#include "ButtonRoomComponent.h"
#include "GameEvent.h"
#include "Collision.h"
#include "RigidbodyComponent.h"
#include "Component.h"
#include "EventBus.h"
#include "RoomManager.h"

ButtonRoomComponent::ButtonRoomComponent(const std::shared_ptr<GameObject>& parent):Component(parent)
{
}

void ButtonRoomComponent::update(const float fDeltaTimeSeconds)
{
}

void ButtonRoomComponent::draw()
{
}

void ButtonRoomComponent::init()
{
}

void ButtonRoomComponent::onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> event)
{
	if(RoomManager::getInstance().getCurrentRoom()->isCompleted())
	{
		return;
	}

	std::shared_ptr<engine::CollisionGameEvent> cge = std::static_pointer_cast<engine::CollisionGameEvent>(event);

	if(cge == nullptr || cge->type != engine::CollisionGameEvent::CollisionType::ENTER)
	{
		return;
	}

	auto col = cge->collision;
	
	if(col->body1->getGameObject().getId() == m_correctButton->getId() || col->body2->getGameObject().getId() == m_correctButton->getId())
	{
		EventBus::getInstance().notify(engine::EventType::ROOMUNLOCKED, std::make_shared<engine::GameEvent>());
	}
	else
	{
		EventBus::getInstance().notify(engine::EventType::DAMAGETAKEN, std::make_shared<engine::GameEvent>());
	}
}
