#include "stdafx.h"
#include "RenderComponent.h"
#include <iostream>


Layer RenderComponent::getLayer()
{
	return m_layer;
}

RenderComponent::RenderComponent(std::shared_ptr<GameObject> parent,Layer layer):
	Component(parent),m_layer(layer)
{

}
