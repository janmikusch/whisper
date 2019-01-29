#pragma once
#include "stdafx.h"
#include "InputComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Layer.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "Animation.h"
#include "AnimatedSprite.h"


class TorchAnimationComponent : public AnimationComponent
{
public:
	TorchAnimationComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& handle, float animationTime = 0.2f);
	void update(const float fDeltaTimeSeconds) override;
	void draw() override;

	void setPosition(const sf::Vector2f &position) override;
	void setRotation(float angle) override;
	void setScale(const sf::Vector2f& factors) override;
	void setOrigin(const sf::Vector2f &origin) override;
	void move(const sf::Vector2f &movement) override;
	void scale(const sf::Vector2f& factor) override;
	void rotate(float angle) override;

private:
	sf::Vector2f m_displace = sf::Vector2f(0,30);
	sf::Sprite m_handle;
};
