#include "stdafx.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "window.h"
#include "RenderComponent.h"
#include "RenderManager.h"
#include "RandomNumber.h"


GameObject::GameObject()
{
	m_identifier = engine::Random::getIntBetween(0, std::numeric_limits<int>::max());
}

GameObject::GameObject(sf::Vector2f position,std::string name):m_name(name)
{
	m_identifier = engine::Random::getIntBetween(0, std::numeric_limits<int>::max());
	this->setPosition(position);
}

void GameObject::update(const float fDeltaTimeSeconds)
{
	for (std::shared_ptr<Component> component : m_components)
	{
		component->update(fDeltaTimeSeconds);
	}
}

void GameObject::draw()
{	
	auto renderComponents = getComponents<RenderComponent>();

	for (auto component : renderComponents)
	{
		if (component != nullptr)
		{
			engine::RenderManager::getInstance().add(component);
		}
	}
}

void GameObject::init()
{
	for(auto it:m_components)
	{
		it->init();
	}
}

void GameObject::addComponent(std::shared_ptr<Component> c)
{
	m_components.push_back(c);
}

void GameObject::setPosition(const sf::Vector2f& position)
{
	Transformable::setPosition(position);
	auto components = this->getComponents<TransformableComponent>();
	for (auto &renderComponent : components)
	{
		renderComponent->setPosition(position);
	}
}

void GameObject::setRotation(float angle)
{
	Transformable::setRotation(angle);
	auto components = this->getComponents<TransformableComponent>();
	for (auto &renderComponent : components)
	{
		renderComponent->setRotation(angle);
	}
}

void GameObject::setScale(const sf::Vector2f& factors)
{
	Transformable::setScale(factors);
	auto components = this->getComponents<TransformableComponent>();
	for (auto &renderComponent : components)
	{
		renderComponent->setScale(factors);
	}
}

void GameObject::setOrigin(const sf::Vector2f& origin)
{
	Transformable::setOrigin(origin);
	auto components = this->getComponents<TransformableComponent>();
	for (auto &renderComponent : components)
	{
		renderComponent->setOrigin(origin);
	}
}

void GameObject::move(const sf::Vector2f& movement)
{
	Transformable::move(movement);
	auto components = this->getComponents<TransformableComponent>();
	for (auto &renderComponent : components)
	{
		renderComponent->move(movement);
	}
}

void GameObject::scale(const sf::Vector2f& factor)
{
	Transformable::scale(factor);
	auto components = this->getComponents<TransformableComponent>();
	for (auto &renderComponent : components)
	{
		renderComponent->scale(factor);
	}
}

void GameObject::rotate(float angle)
{
	Transformable::rotate(angle);
	auto components = this->getComponents<TransformableComponent>();
	for (auto &renderComponent : components)
	{
		renderComponent->rotate(angle);
	}
}

