#pragma once
#include "stdafx.h"
#include "Component.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "RigidbodyComponent.h"


class ColliderComponent : public Component, public TransformableComponent
{
public:
	ColliderComponent(std::shared_ptr<GameObject> parent, const sf::FloatRect &aabb, bool isTrigger = false);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;
	std::shared_ptr<Rigidbody> getRigidbody();
	bool isTrigger();
	sf::FloatRect getShape() { return m_shape; }


	void setPosition(const sf::Vector2f& position) override;
	void setRotation(float angle) override;
	void setScale(const sf::Vector2f& factors) override;
	void setOrigin(const sf::Vector2f& origin) override;
	void move(const sf::Vector2f& movement) override;
	void scale(const sf::Vector2f& factor) override;
	void rotate(float angle) override;

private:
	sf::FloatRect m_shape;
	bool m_isTrigger;
	std::shared_ptr<Rigidbody> m_rigidbody;
};
