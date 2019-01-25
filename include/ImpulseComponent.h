#pragma once
#include "stdafx.h"
#include "Component.h"
#include "RigidbodyComponent.h"


class ImpulseComponent : public Component, public CollisionObserver
{
public:
	ImpulseComponent(std::shared_ptr<GameObject> parent);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;

	void onNotify(const GameObject& collidedWith, const GameObject& ball, engine::GameEvent* event) override;	

};
