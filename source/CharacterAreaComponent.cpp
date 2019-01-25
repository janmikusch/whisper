#include "stdafx.h"
#include "CharacterAreaComponent.h"
#include <SFML/Graphics/VertexArray.hpp>
#include "window.h"
#include "NavigationGraphBuilder.h"
#include "ColliderComponent.h"

CharacterAreaComponent::CharacterAreaComponent(const std::shared_ptr<GameObject>& parent, int id): RenderComponent(parent,Layer::FOREGROUND)
{
}

void CharacterAreaComponent::update(const float fDeltaTimeSeconds)
{
}

void CharacterAreaComponent::draw()
{
	//sf::VertexArray va;
	//va.setPrimitiveType(sf::PrimitiveType::Lines);
	//NavigationGraphBuilder builder;
	//sf::FloatRect rect = m_parent->getComponent<ColliderComponent>()->getShape();
	//builder.init(rect, 10, 10);

	//auto pathStack = builder.getPositionStack(sf::Vector2f{ rect.left,rect.top }, sf::Vector2f{ rect.left + rect.width,rect.top + rect.height });

	//while (!pathStack.empty())
	//{
	//	auto item = pathStack.top();
	//	auto v = sf::Vertex{ item };
	//	v.color = sf::Color::Cyan;
	//	va.append(v);
	//	pathStack.pop();
	//}
	//engine::Window::getInstance().getWindow()->draw(va);
}

void CharacterAreaComponent::init()
{
}
