#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject; //Component uses GameObject, vice versa

class Component
{
public:
	Component(std::shared_ptr<GameObject> parent);
	virtual void update(const float fDeltaTimeSeconds) = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
	GameObject& getGameObject();
protected:
	~Component() = default;
	std::shared_ptr<GameObject> m_parent;
};

class TransformableComponent
{
public:
	virtual void setPosition(const sf::Vector2f &position) = 0;
	virtual void setRotation(float angle) = 0;
	virtual void setScale(const sf::Vector2f& factors) = 0;
	virtual void setOrigin(const sf::Vector2f &origin) = 0;
	virtual void move(const sf::Vector2f &movement) = 0;
	virtual void scale(const sf::Vector2f& factor) = 0;
	virtual void rotate(float angle) = 0;
};