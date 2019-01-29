#pragma once
#include "stdafx.h"
#include "InputComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Layer.h"
#include "RenderComponent.h"
#include "CollisionObserver.h"
#include "Room.h"
#include "Color.h"


class ButtonComponent : public RenderComponent, public TransformableComponent, public CollisionObserver
{
public:
	explicit ButtonComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& texture, engine::Color c);

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

	engine::Color getColor() { return m_color; };

	void onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> event) override;
protected:
	sf::Sprite m_buttonPressed;
	sf::Sprite m_buttonReleased;
	sf::Sprite m_currentState;
	engine::Color m_color;
	bool m_isPressed = false; 
};
