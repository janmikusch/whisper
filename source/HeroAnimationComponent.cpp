#include "stdafx.h"
#include "HeroAnimationComponent.h"
#include <iostream>
#include "window.h"
#include "TextureManager.h"
#include "CharacterMoveComponent.h"

HeroAnimationComponent::HeroAnimationComponent(std::shared_ptr<GameObject> parent, Layer layer, float animationTime) :
	AnimationComponent(parent, layer, animationTime)
{

}

void HeroAnimationComponent::update( const float fDeltaTimeSeconds)
{
	m_frameTime = m_frameClock.restart();
	
	if (m_currentAnimation == "fightUp" || m_currentAnimation == "fightDown" || m_currentAnimation == "fightLeft" || m_currentAnimation == "fightRight" )
		m_animatedSprite.setPosition(m_parent->getPosition() + m_diplace);
	else
		m_animatedSprite.setPosition(m_parent->getPosition());

	m_animatedSprite.setRotation(m_parent->getRotation());
	m_animatedSprite.setOrigin(m_parent->getOrigin());

	m_animatedSprite.play(*m_animations[m_currentAnimation]);
	m_animatedSprite.update(m_frameTime);
}