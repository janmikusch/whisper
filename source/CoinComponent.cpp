#include "stdafx.h"
#include "CoinComponent.h"
#include "RandomNumber.h"

CoinComponent::CoinComponent(const std::shared_ptr<GameObject>& parent, Layer layer, sf::FloatRect aabb): RenderComponent(parent, layer)
{
	m_aabb = aabb;
}

void CoinComponent::update(const float fDeltaTimeSeconds)
{
}

void CoinComponent::draw()
{
	for (auto c : m_coins)
	{
		engine::Window::getInstance().getWindow()->draw(c.shape);
	}
}

void CoinComponent::init()
{
	for (int i = 0; i < m_coinAmount; i++)
	{
		Coin c = Coin();
		c.id = i;
		c.shape = sf::CircleShape(5.0f);
		c.shape.setFillColor(sf::Color(255, 0, 0));
		c.shape.setPosition(calcPos());
		m_coins.push_back(c);
	}
}

sf::Vector2f CoinComponent::calcPos()
{
	float x = engine::Random::getFloatBetween(m_aabb.left, m_aabb.left + m_aabb.width);
	float y = engine::Random::getFloatBetween(m_aabb.top, m_aabb.top + m_aabb.height);

	std::cout << "x: " << m_parent->getScale().x << std::endl;

	return sf::Vector2f(x, y);
}