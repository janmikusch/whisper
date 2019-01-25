#include "stdafx.h"
#include "Component.h"

Component::Component(std::shared_ptr<GameObject> parent):m_parent(parent)
{}

GameObject& Component::getGameObject()
{
	return *m_parent;
}

