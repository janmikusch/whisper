#pragma once
#include "stdafx.h"
#include "Component.h"
#include "TextGuiComponent.h"

class TorchRoomSolverComponent : public TextGuiComponent
{
public:
	TorchRoomSolverComponent(std::shared_ptr<GameObject> parent, int answer, sf::Texture& texture);
	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;

	void setPosition(const sf::Vector2f& position) override;
	void setRotation(float angle) override;
	void setScale(const sf::Vector2f& factors) override;
	void setOrigin(const sf::Vector2f& origin) override;
	void move(const sf::Vector2f& movement) override;
	void scale(const sf::Vector2f& factor) override;
	void rotate(float angle) override;
private:
	int m_answer; //=42
	sf::Sprite m_background;
};
