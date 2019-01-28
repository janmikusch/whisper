#include "stdafx.h"
#include "HeroAnimationComponent.h"
#include <iostream>
#include "window.h"
#include "TextureManager.h"

void HeroAnimationComponent::update( const float fDeltaTimeSeconds)
{
	m_frameTime = m_frameClock.restart();
	
	m_animatedSprite.setPosition(m_parent->getPosition());
	m_animatedSprite.setRotation(m_parent->getRotation());
	m_animatedSprite.setOrigin(m_parent->getOrigin());

	m_animatedSprite.play(*m_animations[m_currentAnimation]);
	m_animatedSprite.update(m_frameTime);
}