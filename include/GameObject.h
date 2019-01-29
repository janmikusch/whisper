#pragma once
#include "stdafx.h"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Component.h"
#include <memory>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Err.hpp>


class Component; //GameObject uses Component, vice versa

class GameObject:public sf::Transformable
{
public:
	GameObject();
	GameObject(sf::Vector2f position,std::string name);
	void update(const float fDeltaTimeSeconds);
	void draw();
	void init();
	void addComponent(std::shared_ptr<Component> c);

	//forward to components
	void setPosition(const sf::Vector2f &position);
	void setRotation(float angle);
	void setScale(const sf::Vector2f& factors);
	void setOrigin(const sf::Vector2f &origin);
	void move(const sf::Vector2f &movement);
	void scale(const sf::Vector2f& factor);
	void rotate(float angle);
	

	std::string getName() const { return  m_name; };
	int getId() const { return  m_identifier; };

	template<class T>
	std::shared_ptr<T> getComponent(); // where T is Component
	template<class T>
	std::vector<std::shared_ptr<T>> getComponents(); // where T is Component
private:
	std::vector<std::shared_ptr<Component>> m_components{};
	std::string m_name;
	int m_identifier;
};


template <class T>
std::shared_ptr<T> GameObject::getComponent()
{
	for (std::shared_ptr<Component> component : m_components)
	{
		std::shared_ptr<T> c = std::dynamic_pointer_cast<T>(component);
		if(c != nullptr)
		{
			return c;
		}
	}
	//sf::err() << "Component not found: " << typeid(T).name();
	return nullptr;
}

template <class T>
std::vector<std::shared_ptr<T>> GameObject::getComponents()
{
	std::vector < std::shared_ptr<T> > result{};
	for (std::shared_ptr<Component> component : m_components)
	{
		std::shared_ptr<T> c = std::dynamic_pointer_cast<T>(component);
		if (c != nullptr)
		{
			result.push_back(c);
		}
	}
	return result;
}
