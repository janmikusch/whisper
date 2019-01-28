#pragma once
#include "stdafx.h"
#include "InputComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Layer.h"
#include "RenderComponent.h"


class BoundingboxComponent : public RenderComponent, public TransformableComponent
{
public:
	explicit BoundingboxComponent(std::shared_ptr<GameObject> parent, sf::FloatRect& aabb, Layer layer = Layer::DEBUG_BOUNDINGBOX, sf::Vector2f displacement = sf::Vector2f(0,0));

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;

	void setPosition(const sf::Vector2f &position) override;
	void setRotation(float angle) override;
	void setScale(const sf::Vector2f& factors) override;
	void setOrigin(const sf::Vector2f &origin) override;
	void move(const sf::Vector2f &movement) override;
	void scale(const sf::Vector2f& factor) override;
	void rotate(float angle) override;

	void setColor(sf::Color c);

protected:
	// The debug geometry to visualize the bounding geometry of the object.
	// Can be part of a BBoxCollisionComponent.
	sf::RectangleShape m_debugGeometry;
	sf::Vector2f m_displacement;
};
