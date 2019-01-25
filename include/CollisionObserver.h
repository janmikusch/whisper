#pragma once
#include "stdafx.h"
#include "GameObject.h"

namespace engine {
	struct GameEvent;
}

class CollisionObserver
{
public:
	virtual void onNotify(const GameObject& collidedWith, const GameObject& ball, engine::GameEvent* event) = 0;
};
