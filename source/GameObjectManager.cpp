#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager& GameObjectManager::getInstance()
{
	static GameObjectManager instance;
	return instance;
}

void GameObjectManager::add(std::shared_ptr<GameObject> gameObject)
{	
	m_toAdd.push(gameObject);
}

void GameObjectManager::remove(std::shared_ptr<GameObject> gameObject)
{
	m_toRemove.push(gameObject);
}

void GameObjectManager::applyChanges()
{
	while(!m_toAdd.empty())
	{
		std::shared_ptr<GameObject> obj = m_toAdd.front();
		m_toAdd.pop();
		m_gameObjects.push_back(obj);
	}

	while(!m_toRemove.empty())
	{
		std::shared_ptr<GameObject> obj = m_toRemove.front();
		m_toRemove.pop();
		auto position = std::find(m_gameObjects.begin(), m_gameObjects.end(), obj);
		if (position != m_gameObjects.end())
		{
			m_gameObjects.erase(position);
		}
	}
}

void GameObjectManager::clear()
{
	m_gameObjects.clear();

	{
		std::queue<std::shared_ptr<GameObject>> empty;
		std::swap(m_toAdd, empty);
	}
	{
		std::queue<std::shared_ptr<GameObject>> empty;
		std::swap(m_toRemove, empty);
	}
}

std::vector<std::shared_ptr<GameObject>> GameObjectManager::getList() const
{
	return m_gameObjects;
}

std::shared_ptr<GameObject> GameObjectManager::getFirstGameObject(std::string name)
{
	for (auto object : GameObjectManager::getInstance().getList())
	{
		if (object->getName() == name)
			return object;
	}
}

std::vector<std::shared_ptr<GameObject>> GameObjectManager::getGameObjectList(std::string name)
{
	std::vector<std::shared_ptr<GameObject>> list;
	for (auto object : GameObjectManager::getInstance().getList())
	{
		if (object->getName() == name)
			list.push_back(object);
	}
	return list;
}

