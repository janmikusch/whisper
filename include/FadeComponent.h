#pragma once
#include "stdafx.h"
#include "InputComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Layer.h"
#include "RenderComponent.h"


class FadeComponent : public RenderComponent, public TransformableComponent, public EventObserver
{
public:
	explicit FadeComponent(std::shared_ptr<GameObject> parent, Layer layer);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init();

	void setPosition(const sf::Vector2f &position) override;
	void setRotation(float angle) override;
	void setScale(const sf::Vector2f& factors) override;
	void setOrigin(const sf::Vector2f &origin) override;
	void move(const sf::Vector2f &movement) override;
	void scale(const sf::Vector2f& factor) override;
	void rotate(float angle) override;

	void setColor(sf::Color c);
	void setSpeed(float speed);
	void onNotify(engine::EventType type, std::shared_ptr<engine::GameEvent> gameEvent) override;
	void addToEventBus(engine::EventType e);
protected:
	sf::RectangleShape m_rect;
	float m_alpha;
	float m_speed = 320;
};
