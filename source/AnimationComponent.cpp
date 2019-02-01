#include "stdafx.h"
#include "AnimationComponent.h"
#include <iostream>
#include "window.h"
#include "TextureManager.h"

AnimationComponent::AnimationComponent(std::shared_ptr<GameObject> parent, Layer layer, float animationTime) :
	RenderComponent(parent, layer), m_animatedSprite(sf::seconds(animationTime), true, false)
{
	m_animatedSprite.setPosition(m_parent->getPosition());
}

void AnimationComponent::update( const float fDeltaTimeSeconds)
{
	m_frameTime = m_frameClock.restart();

	m_animatedSprite.setPosition(m_parent->getPosition());
	m_animatedSprite.setRotation(m_parent->getRotation());
	m_animatedSprite.setOrigin(m_parent->getOrigin());

	m_animatedSprite.play(*m_animations[m_currentAnimation]);
	m_animatedSprite.update(m_frameTime);
}

void AnimationComponent::init()
{
	
}

void AnimationComponent::setPosition(const sf::Vector2f& position)
{
	m_animatedSprite.setPosition(position);
}

void AnimationComponent::setRotation(float angle)
{
	m_animatedSprite.setRotation(angle);
}

void AnimationComponent::setScale(const sf::Vector2f& factors)
{
	m_animatedSprite.setScale(factors);
}

void AnimationComponent::setOrigin(const sf::Vector2f& origin)
{
	m_animatedSprite.setOrigin(origin);
}

void AnimationComponent::move(const sf::Vector2f& movement)
{
	m_animatedSprite.move(movement);
}

void AnimationComponent::scale(const sf::Vector2f& factor)
{
	m_animatedSprite.scale(factor);
}

void AnimationComponent::rotate(float angle)
{
	m_animatedSprite.rotate(angle);
}

void AnimationComponent::setAnimation(std::string name)
{
	auto it = m_animations.find(name);
	if(it == m_animations.end())
	{
		sf::err() << "Animation " + name + " not found";
		return;
	}

	m_currentAnimation = name;
}

void AnimationComponent::addAnimation(Animation anim, std::string name)
{
	auto it = m_animations.find(name);
	if (it != m_animations.end())
	{
		sf::err() << "Animation " + name + " exists";
		return;
	}

	m_animations.insert_or_assign(name, std::make_shared<Animation>(anim));

}


void AnimationComponent::draw()
{
	if(m_currentAnimation == "")
	{
		sf::err() << "no animation is set";
		return;
	}

	engine::Window::getInstance().getWindow()->draw(m_animatedSprite);
	//RenderManagerInstance.AddRenderable(m_layer,SpriteRenderer{&m_sprite});
	sf::VertexArray lines(sf::Points, 1);
	lines.append(sf::Vertex{ m_parent->getPosition() });
	engine::Window::getInstance().getWindow()->draw(lines);
}

void AnimationComponent::setLoop(bool loop)
{
	m_animatedSprite.setLooped(loop);
}
