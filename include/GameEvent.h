#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Room.h"

struct Collision;

namespace engine
{
	enum EventType { DOORENTER, GAMESTART,GAMEQUIT, GAMECONTINUE, GAMEPAUSE, GAMEOVER
	};

	struct GameEvent
	{
		
	};

	struct CollisionGameEvent : public GameEvent
	{
		enum CollisionType{STAY,ENTER,EXIT};
		CollisionType type = STAY;
		std::shared_ptr<Collision> collision;

	};

	struct DoorEnterGameEvent: public GameEvent
	{
		Room::Direction direction;
	};
}