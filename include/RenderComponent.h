#pragma once
#include "stdafx.h"
#include "InputComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Layer.h"


class RenderComponent : public Component
{
public:
	virtual void update(const float fDeltaTimeSeconds) override = 0;
	virtual void draw() override = 0;
	virtual void init() override = 0;

	Layer getLayer();
protected:
	explicit RenderComponent(std::shared_ptr<GameObject> parent, Layer layer = Layer::NOTDEFINED);

	Layer m_layer;
};
