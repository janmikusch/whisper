#pragma once
#include "stdafx.h"
#include <map>
#include "Layer.h"
#include "RenderComponent.h"

namespace engine
{
	class RenderManager
	{
		RenderManager() = default;
	public:
		void add(std::shared_ptr<RenderComponent> component);
		void renderAll();
		void clear();
		static RenderManager& getInstance();
	private:
		std::map < Layer, std::vector < std::shared_ptr<RenderComponent> > > m_renderMap;
		void renderLayer(Layer l);
	};
}
