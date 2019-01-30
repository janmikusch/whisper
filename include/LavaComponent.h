#pragma once
#include "stdafx.h"
#include "InputComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "SpriteComponent.h"
#include "CollisionObserver.h"

class LavaComponent : public SpriteComponent, public TransformableComponent, public CollisionObserver
{
public:
	explicit LavaComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& texture, sf::IntRect textureRect);

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

	void onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> gameEvent) override;

protected:
	sf::Sprite m_sprite;
	bool m_isVisible = false;
};
