#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameStateManager.h"
#include "GameObject.h"

enum Layer
{
	NOTDEFINED,BACKGROUND1, BACKGROUND2, BACKGROUND3,MIDDLE1, MIDDLE2, MIDDLE3, FOREGROUND1, FOREGROUND2, FOREGROUND3, DEBUG_BOUNDINGBOX
};

class StringToLayer
{
public:
	static Layer getLayer(std::string str)
	{
		static std::map<std::string, Layer> stringToLayer = {
			{"foreground1",Layer::FOREGROUND1},
			{"foreground2",Layer::FOREGROUND2},
			{"foreground3",Layer::FOREGROUND3},
			{"middle1",Layer::MIDDLE1},
			{"middle2",Layer::MIDDLE2},
			{"middle3",Layer::MIDDLE3},
			{"background1",Layer::BACKGROUND1},
			{"background2",Layer::BACKGROUND2},
			{"background3",Layer::BACKGROUND3}
		};

		if (stringToLayer.find(str) == stringToLayer.end())
		{
			return Layer::NOTDEFINED;
		}
		return stringToLayer[str];
	}
private:
};