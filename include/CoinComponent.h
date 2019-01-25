#pragma once
#include "stdafx.h"
#include "RenderComponent.h"
#include "window.h"

struct Coin;

class CoinComponent : public RenderComponent
{
public:
	explicit CoinComponent(const std::shared_ptr<GameObject>& parent, Layer layer, sf::FloatRect m_aabb);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;
private:
	sf::FloatRect m_aabb;
	const int m_coinAmount = 6;
	std::vector<Coin> m_coins;

	sf::Vector2f calcPos();
};

struct Coin
{
	int id;
	//sf::Vector2f position;
	sf::CircleShape shape;
};