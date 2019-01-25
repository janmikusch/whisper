#include "stdafx.h"
#include "CameraComponent.h"
#include <SFML/Graphics/View.hpp>
#include "window.h"

CameraComponent::CameraComponent(std::shared_ptr<GameObject> parent):
	Component(parent)
{
}

void CameraComponent::update(const float fDeltaTimeSeconds)
{
}

void CameraComponent::init()
{
	m_view = engine::Window::getInstance().getWindow()->getView();
	m_view.zoom(1.1f);
	m_view.setCenter(sf::Vector2f(240.0f,320.0f));
	engine::Window::getInstance().getWindow()->setView(m_view);
}

void CameraComponent::draw()
{
}

void CameraComponent::reset()
{
	m_view.zoom(2.0f);
	engine::Window::getInstance().getWindow()->setView(engine::Window::getInstance().getWindow()->getDefaultView());
	
}
