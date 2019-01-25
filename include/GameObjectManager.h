#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include <queue>

class GameObjectManager
{
public:
	static GameObjectManager& getInstance();
	void add(std::shared_ptr<GameObject> gameObject);
	void remove(std::shared_ptr<GameObject> gameObject);
	void applyChanges();
	void clear();
	std::vector < std::shared_ptr<GameObject>> getList() const;

	std::shared_ptr<GameObject> getFirstGameObject(std::string name);
	std::vector<std::shared_ptr<GameObject>> getGameObjectList(std::string name);
private:
	GameObjectManager() = default;
	std::vector<std::shared_ptr<GameObject>> m_gameObjects;
	std::queue<std::shared_ptr<GameObject>> m_toAdd;
	std::queue<std::shared_ptr<GameObject>> m_toRemove;
};
