#include "stdafx.h"
#include "RenderManager.h"

void engine::RenderManager::renderLayer(Layer l)
{
	if(m_renderMap.find(l) == m_renderMap.end())
		return;
	auto currentLayer = m_renderMap[l];
	std::sort(currentLayer.begin(), currentLayer.end(),
		[](std::shared_ptr<RenderComponent> const& a, std::shared_ptr<RenderComponent> const& b)
		{ return a->getGameObject().getPosition().y < b->getGameObject().getPosition().y; });
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
	renderLayer(Layer::BACKGROUND1);
	renderLayer(Layer::BACKGROUND2);
	renderLayer(Layer::BACKGROUND3);
	renderLayer(Layer::BACKGROUND4);
	renderLayer(Layer::BACKGROUND5);
	renderLayer(Layer::MIDDLE1);
	renderLayer(Layer::MIDDLE2);
	renderLayer(Layer::MIDDLE3);
	renderLayer(Layer::FOREGROUND1);
	renderLayer(Layer::FOREGROUND2);
	renderLayer(Layer::FOREGROUND3);

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
