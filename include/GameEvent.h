#pragma once
#include "stdafx.h"
#include "GameObject.h"

struct Collision;

namespace engine
{
	struct GameEvent
	{
		
	};

	struct CollisionGameEvent : GameEvent
	{
		enum CollisionType{STAY,ENTER,EXIT};
		CollisionType type = STAY;
		std::shared_ptr<Collision> collision;

	};	
}