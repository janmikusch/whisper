#include "stdafx.h"
#include "RenderManager.h"

void engine::RenderManager::renderLayer(Layer l)
{
	if(m_renderMap.find(l) == m_renderMap.end())
		return;
	auto currentLayer = m_renderMap[l];
	for (auto renderObject : currentLayer)
	{
		renderObject->draw();
	}
}

void engine::RenderManager::add(std::shared_ptr<RenderComponent> component)
{
	m_renderMap[component->getLayer()].push_back(component);
}

void engine::RenderManager::renderAll()
{
	renderLayer(Layer::NOTDEFINED);
	renderLayer(Layer::BACKGROUND);
	renderLayer(Layer::MIDDLE);
	renderLayer(Layer::OBJECTS);
	renderLayer(Layer::PLAYER);
	renderLayer(Layer::FOREGROUND);

#ifdef _DEBUG
	renderLayer(Layer::DEBUG_BOUNDINGBOX);
#endif
}

//remove all RenderComponents
void engine::RenderManager::clear()
{
	m_renderMap.clear();
}

engine::RenderManager& engine::RenderManager::getInstance()
{
	static RenderManager m_instance;
	return m_instance;
}
