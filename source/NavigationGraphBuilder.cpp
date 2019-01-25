#include "stdafx.h"
#include "NavigationGraphBuilder.h"
#include <SFML/Graphics/Rect.hpp>
#include "PhysicsManager.h"
#include "GameObjectManager.h"
#include "ColliderComponent.h"

void NavigationGraphBuilder::init(sf::FloatRect area, int node_count_x,	int node_count_y)
{
	auto old = std::vector<std::vector<NavigationNode>>{};
	m_node2DArray.swap(old); // empty list

	m_position = sf::Vector2f{area.left,area.top};
	m_node_count_x = node_count_x;
	m_node_count_y = node_count_y;
	m_node_height = (area.height) / node_count_y;
	m_node_width = (area.width) / node_count_x;

	for (int x = 0; x <= node_count_x; ++x)
	{
		auto colum = std::vector<NavigationNode>{};
		for (int y = 0; y <= node_count_y; ++y)
		{
			sf::Vector2f position = m_position + sf::Vector2f(x * m_node_width, y * m_node_height);
			auto nodeArea = sf::FloatRect{ 
				position.x,
				position.y ,
				m_node_width,
				m_node_height,
			};
			float nodeCost = getNodeCost(nodeArea);
			colum.push_back(NavigationNode{ nodeCost,position });
		}
		m_node2DArray.push_back(colum);
	}

#ifdef _DEBUG
	sf::err() << "Generated Nodes:" << std::endl;

	for (int y = 0; y < node_count_y; ++y)
	{
		for (int x = 0; x < node_count_x; ++x)
		{
			std::string s = "1";
			if (m_node2DArray[x][y].ownCost > 10)
				s = "X";
			sf::err() << s;
		}
		sf::err() << std::endl;
	}
#endif
}

std::stack<sf::Vector2f> NavigationGraphBuilder::getPositionStack(sf::Vector2f from, sf::Vector2f to)
{
	std::stack<sf::Vector2f> posStack;
	posStack.push(to);

	std::shared_ptr<NodeRecord> record = getPath(from, to);
	while (record != nullptr)
	{
		posStack.push(record->node->position);
		record = record->record;
	}
	return posStack;
}

std::shared_ptr<NodeRecord> NavigationGraphBuilder::getPath(sf::Vector2f from, sf::Vector2f to)
{
	int x = 0, y = 0;
	x = (from.x - m_position.x) / m_node_width;
	y = (from.y - m_position.y) / m_node_height;
	NavigationNode& startNode = getNode(x, y);

	x = (to.x - m_position.x) / m_node_width;
	y = (to.y - m_position.y) / m_node_height;
	NavigationNode& goalNode = getNode(x, y);

	auto heuristic = [](NavigationNode& a, NavigationNode& b) -> float
	{
		sf::Vector2f pos = a.position - b.position;
		return sqrt(pos.x * pos.x + pos.y * pos.y);
	};

	auto comp = [](std::shared_ptr<NodeRecord> a, std::shared_ptr<NodeRecord> b) -> bool
	{
		return (a->costSoFar + a->heuristic) < (b->costSoFar + b->heuristic);
	};

	std::shared_ptr<NodeRecord> current = nullptr;
	std::list<std::shared_ptr<NodeRecord>> open;
	std::list<std::shared_ptr<NodeRecord>> closed;
	auto startRecord = std::make_shared<NodeRecord>(NodeRecord{ &startNode,startNode.ownCost, heuristic(startNode,goalNode),nullptr });
	open.push_back(startRecord);

	while (open.size())
	{
		current = *open.begin();
		open.remove(current);

		if (current->node == &goalNode)
			break;

		//add nodeRecords for each side
		NavigationNode* newNode = nullptr;
		std::shared_ptr<NodeRecord> newRecord = nullptr;

		std::stack<NavigationNode*> navStack;

		navStack.push(getNodeUp(*current->node));
		navStack.push(getNodeUpRight(*current->node));
		navStack.push(getNodeRight(*current->node));
		navStack.push(getNodeDownRight(*current->node));
		navStack.push(getNodeDown(*current->node));
		navStack.push(getNodeDownLeft(*current->node));
		navStack.push(getNodeLeft(*current->node));
		navStack.push(getNodeUpLeft(*current->node));

		while (!navStack.empty())
		{
			newNode = navStack.top();
			navStack.pop();

			if (newNode == nullptr)
			{
				continue;
			}


			// find newNode in closed and open list of NodeRecord
			// lambda expression is used to compare with content 
			// of NodeRecord directly
			auto itClosed = find_if(closed.begin(), closed.end(),
				[&newNode](std::shared_ptr<NodeRecord> a)->bool
			{ return a->node == newNode; });
			auto itOpen = find_if(open.begin(), open.end(),
				[&newNode](std::shared_ptr<NodeRecord> a)->bool
			{ return a->node == newNode; });

			float costSoFar = current->costSoFar + newNode->ownCost;				
			float endNodeCost = costSoFar + heuristic(*newNode, goalNode);

			float heu = heuristic(*newNode, goalNode);

			if (itClosed != closed.end())
			{
				continue;
			}
			else if (itOpen != open.end())
			{
				newRecord = *itOpen;
				if (newRecord->costSoFar <= endNodeCost)
					continue;
			}
			else
			{
				newRecord = std::make_shared<NodeRecord>();
			}

			newRecord->node = newNode;
			newRecord->costSoFar = costSoFar;
			newRecord->heuristic = heu;
			newRecord->record = current;

			if (find(open.begin(), open.end(), newRecord) == open.end())
				open.push_back(newRecord);

			stable_sort(open.begin(), open.end(), comp);

		}
		open.remove(current);
		closed.push_back(current);
	}
	return current;
}

NavigationNode* NavigationGraphBuilder::getNodeUp(const NavigationNode& baseNode)
{ 
	int x, y;
	getNodePosition(baseNode, x, y);
	y--;
	if (y < 0 || y > m_node_count_y || x < 0 || x > m_node_count_x)
	{
		return nullptr;
	}
	return &getNode(x, y);
}

NavigationNode* NavigationGraphBuilder::getNodeUpRight(const NavigationNode& baseNode)
{
	int x, y;
	getNodePosition(baseNode, x, y);
	y--;
	x++;
	if (y < 0 || y > m_node_count_y || x < 0 || x > m_node_count_x)
	{
		return nullptr;
	}
	return &getNode(x, y);
}

NavigationNode* NavigationGraphBuilder::getNodeRight(const NavigationNode& baseNode)
{
	int x, y;
	getNodePosition(baseNode, x, y);
	x++;
	if (y < 0 || y > m_node_count_y || x < 0 || x > m_node_count_x)
	{
		return nullptr;
	}
	return &getNode(x, y);
}

NavigationNode* NavigationGraphBuilder::getNodeDownRight(const NavigationNode& baseNode)
{
	int x, y;
	getNodePosition(baseNode, x, y);
	y++;
	x++;
	if (y < 0 || y > m_node_count_y || x < 0 || x > m_node_count_x)
	{
		return nullptr;
	}
	return &getNode(x, y);
}

NavigationNode* NavigationGraphBuilder::getNodeDown(const NavigationNode& baseNode)
{
	int x, y;
	getNodePosition(baseNode, x, y);
	y++;
	if (y < 0 || y > m_node_count_y || x < 0 || x > m_node_count_x)
	{
		return nullptr;
	}
	return &getNode(x, y);
}

NavigationNode* NavigationGraphBuilder::getNodeDownLeft(const NavigationNode& baseNode)
{
	int x, y;
	getNodePosition(baseNode, x, y);
	y++;
	x--;
	if (y < 0 || y > m_node_count_y || x < 0 || x > m_node_count_x)
	{
		return nullptr;
	}
	return &getNode(x, y);
}

NavigationNode* NavigationGraphBuilder::getNodeLeft(const NavigationNode& baseNode)
{
	int x, y;
	getNodePosition(baseNode, x, y);
	x--;
	if (y < 0 || y > m_node_count_y || x < 0 || x > m_node_count_x)
	{
		return nullptr;
	}
	return &getNode(x, y);
}

NavigationNode* NavigationGraphBuilder::getNodeUpLeft(const NavigationNode& baseNode)
{
	int x, y;
	getNodePosition(baseNode, x, y);
	y--;
	x--;
	if (y < 0 || y > m_node_count_y || x < 0 || x > m_node_count_x)
	{
		return nullptr;
	}
	return &getNode(x, y);
}


NavigationNode& NavigationGraphBuilder::getNode(int x, int y)
{
	if (x < 0)
		x = 0;
	if (x > m_node_count_x)
		x = m_node_count_x;
	if (y < 0)
		y = 0;
	if (y > m_node_count_y)
		y = m_node_count_y;
	return m_node2DArray[x][y];
}

void NavigationGraphBuilder::getNodePosition(const NavigationNode& baseNode, int& x, int& y)
{
	auto pos = baseNode.position - m_position;
	x = pos.x / m_node_width;
	y = pos.y / m_node_height;
}

float NavigationGraphBuilder::getNodeCost(sf::FloatRect& nodeArea)
{
	sf::Vector2f normal;
	float penetration;
	for (auto it:GameObjectManager::getInstance().getGameObjectList("staticCollider"))
	{
		if (PhysicsManager::getInstance().AABBvsAABB(nodeArea,it->getComponent<ColliderComponent>()->getShape(),normal,penetration))
		{
			return m_collisionCost;
		}
	}
	return 1.0f;
}
