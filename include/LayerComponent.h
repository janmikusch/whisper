#pragma once
#include "stdafx.h"
#include "InputComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Layer.h"
#include "RenderComponent.h"


class LayerComponent : public RenderComponent, public TransformableComponent
{
public:
	explicit LayerComponent(std::shared_ptr<GameObject> parent, Layer layer, float scaleX = 1.0f, float scaleY = 1.0f);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;
	void setAllSprites(std::vector<std::shared_ptr<sf::Sprite>> sprites);
	void addSprite(std::shared_ptr<sf::Sprite> sprite);

	void setPosition(const sf::Vector2f &position) override;
	void setRotation(float angle) override;
	void setScale(const sf::Vector2f& factors) override;
	void setOrigin(const sf::Vector2f &origin) override;
	void move(const sf::Vector2f &movement) override;
	void scale(const sf::Vector2f& factor) override;
	void rotate(float angle) override;
protected:
	std::vector<std::shared_ptr<sf::Sprite>> m_sprites;
};
