#pragma once
#include "stdafx.h"
#include "Component.h"
#include "CollisionObserver.h"

class ButtonRoomComponent: public Component, public CollisionObserver
{
public:
	ButtonRoomComponent(const std::shared_ptr<GameObject>& parent);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;

	void setCorrectButton(std::shared_ptr<GameObject> correctButton) { m_correctButton = correctButton; }
	void onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> event) override;;
	
private:
	std::shared_ptr<GameObject> m_correctButton;
};
