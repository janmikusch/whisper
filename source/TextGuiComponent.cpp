#include "stdafx.h"
#include "SpriteComponent.h"
#include <iostream>
#include "TextGuiComponent.h"
#include "window.h"

TextGuiComponent::TextGuiComponent(std::shared_ptr<GameObject> parent,Layer layer, sf::Text text):
	RenderComponent(parent,layer),m_text(text)
{

}

void TextGuiComponent::setText(sf::Text t)
{
	m_text = t;
}

void TextGuiComponent::setTextContent(std::string text)
{
	m_text.setString(text);
}

void TextGuiComponent::update(const float fDeltaTimeSeconds)
{
	m_text.setPosition(m_parent->getPosition());
}

void TextGuiComponent::init()
{

}

void TextGuiComponent::setPosition(const sf::Vector2f& position)
{
	m_text.setPosition(position);
}

void TextGuiComponent::setRotation(float angle)
{
	m_text.setRotation(angle);
}

void TextGuiComponent::setScale(const sf::Vector2f& factors)
{
	m_text.setScale(factors);
}

void TextGuiComponent::setOrigin(const sf::Vector2f& origin)
{
	m_text.setOrigin(origin);
}

void TextGuiComponent::move(const sf::Vector2f& movement)
{
	m_text.move(movement);
}

void TextGuiComponent::scale(const sf::Vector2f& factor)
{
	m_text.scale(factor);
}

void TextGuiComponent::rotate(float angle)
{
	m_text.rotate(angle);
}

void TextGuiComponent::draw()
{
	engine::Window::getInstance().getWindow()->draw(m_text);
}
