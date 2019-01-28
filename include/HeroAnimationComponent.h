#pragma once
#include "stdafx.h"
#include "InputComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Layer.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "Animation.h"
#include "AnimatedSprite.h"


class HeroAnimationComponent : public AnimationComponent
{
public:
	HeroAnimationComponent(std::shared_ptr<GameObject> parent, Layer layer, float animationTime = 0.2f);
	void update(const float fDeltaTimeSeconds) override;

private:
	sf::Vector2f m_diplace = sf::Vector2f(-64,0);
};
