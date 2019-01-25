#pragma once
#include "stdafx.h"
#include <SFML/System/Vector2.hpp>
#include <yvals_core.h>
#include <memory>


struct NavigationNode
{
	float ownCost;
	sf::Vector2f position;
};

struct NodeRecord
{
	NavigationNode* node;
	float costSoFar;
	float heuristic;
	std::shared_ptr<NodeRecord> record;
};
