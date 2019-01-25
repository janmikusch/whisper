#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameStateManager.h"
#include "GameObject.h"

enum Layer
{
	NOTDEFINED,BACKGROUND,MIDDLE,FOREGROUND, OBJECTS,PLAYER, DEBUG_BOUNDINGBOX
};

class StringToLayer
{
public:
	static Layer getLayer(std::string str)
	{
		static std::map<std::string, Layer> stringToLayer = {
			{"foreground",Layer::FOREGROUND},
			{"background",Layer::BACKGROUND},
			{"player",Layer::PLAYER},
			{"objects",Layer::OBJECTS},
			{"middle",Layer::MIDDLE}
		};

		if (stringToLayer.find(str) == stringToLayer.end())
		{
			return Layer::NOTDEFINED;
		}
		return stringToLayer[str];
	}
private:
};