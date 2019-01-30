#include "stdafx.h"
#include "TorchRoomSolverComponent.h"
#include "TorchRoomCreator.h"
#include "GameObjectManager.h"
#include "TorchAnimationComponent.h"
#include "FontManager.h"
#include "window.h"

TorchRoomSolverComponent::TorchRoomSolverComponent(std::shared_ptr<GameObject> parent, int answer, sf::Texture& texture):
TextGuiComponent(parent,Layer::BACKGROUND3,sf::Text{std::to_string(answer),FontManager::getInstance().getFont("Blood"),50}),
m_answer(answer)
{
	m_text.setFillColor(sf::Color::Red);
	m_background = sf::Sprite(texture);
}

void TorchRoomSolverComponent::update(const float fDeltaTimeSeconds)
{
	GameObjectManager& gom = GameObjectManager::getInstance();

	auto toggleTorches = gom.getGameObjectList("toggleTorch");

	int valueSum = 0;

	for(auto it:toggleTorches)
	{
		if(it == nullptr)
			continue;
		auto value = TorchRoomCreator::getValueFromColor(it->getComponent<TorchAnimationComponent>()->getFlameColor());
		valueSum += value;
	}

	if(m_answer == valueSum)
	{
		EventBus::getInstance().notify(engine::EventType::ROOMUNLOCKED, std::shared_ptr<engine::GameEvent>());
	}

	setPosition(m_parent->getPosition());
}

void TorchRoomSolverComponent::draw()
{
	engine::Window::getInstance().getWindow()->draw(m_background);
	TextGuiComponent::draw();
}

void TorchRoomSolverComponent::init()
{
	TextGuiComponent::init();
}

void TorchRoomSolverComponent::setPosition(const sf::Vector2f& position)
{
	m_background.setPosition(m_parent->getPosition());
	sf::Vector2f displacement{ 40,30 };
	m_text.setPosition(m_parent->getPosition() + displacement);
}

void TorchRoomSolverComponent::setRotation(float angle)
{
	TextGuiComponent::setRotation(angle);

}

void TorchRoomSolverComponent::setScale(const sf::Vector2f& factors)
{
	TextGuiComponent::setScale(factors);

}

void TorchRoomSolverComponent::setOrigin(const sf::Vector2f& origin)
{
	TextGuiComponent::setOrigin(origin);

}

void TorchRoomSolverComponent::move(const sf::Vector2f& movement)
{
	TextGuiComponent::move(movement);

}

void TorchRoomSolverComponent::scale(const sf::Vector2f& factor)
{
	TextGuiComponent::scale(factor);

}

void TorchRoomSolverComponent::rotate(float angle)
{
	TextGuiComponent::rotate(angle);

}
