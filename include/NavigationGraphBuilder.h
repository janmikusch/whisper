#pragma once
#include "stdafx.h"
#include <SFML/System/Vector2.hpp>
#include <stack>
#include "NavigationNode.h"
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <memory>

class NavigationGraphBuilder
{
public:
	NavigationGraphBuilder() = default;
	void init(sf::FloatRect area, int node_count_x, int node_count_y);
	std::stack<sf::Vector2f> getPositionStack(sf::Vector2f from, sf::Vector2f to);
	std::shared_ptr<NodeRecord> getPath(sf::Vector2f from, sf::Vector2f to);


private:
	float getNodeCost(sf::FloatRect& nodeArea);
	void getNodePosition(const NavigationNode& baseNode, int& x, int& y);

	NavigationNode* getNodeUp(const NavigationNode& baseNode);
	NavigationNode* getNodeUpRight(const NavigationNode& baseNode);
	NavigationNode* getNodeRight(const NavigationNode& baseNode);
	NavigationNode* getNodeDownRight(const NavigationNode& baseNode);
	NavigationNode* getNodeDown(const NavigationNode& baseNode);
	NavigationNode* getNodeDownLeft(const NavigationNode& baseNode);
	NavigationNode* getNodeLeft(const NavigationNode& baseNode);
	NavigationNode* getNodeUpLeft(const NavigationNode& baseNode);
	NavigationNode& getNode(int x, int y);

	sf::Vector2f m_position;
	float m_node_height;
	float m_node_width;
	int m_node_count_x; 
	int m_node_count_y;

	std::vector<std::vector<NavigationNode>> m_node2DArray;

	const float m_collisionCost = 100000.0f;
};
