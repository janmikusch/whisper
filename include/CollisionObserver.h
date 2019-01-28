#pragma once
#include "stdafx.h"
#include "GameObject.h"

namespace engine {
	struct GameEvent;
}

class CollisionObserver
{
public:
	virtual void onNotify(const GameObject& collidedWith, engine::GameEvent* event) = 0;
};
