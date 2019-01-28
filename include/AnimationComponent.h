#pragma once
#include "stdafx.h"
#include "InputComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Layer.h"
#include "RenderComponent.h"
#include "Animation.h"
#include "AnimatedSprite.h"


class AnimationComponent : public RenderComponent, public TransformableComponent
{
public:
	explicit AnimationComponent(std::shared_ptr<GameObject> parent, Layer layer);

	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;

	void setPosition(const sf::Vector2f &position) override;
	void setRotation(float angle) override;
	void setScale(const sf::Vector2f& factors) override;
	void setOrigin(const sf::Vector2f &origin) override;
	void move(const sf::Vector2f &movement) override;
	void scale(const sf::Vector2f& factor) override;
	void rotate(float angle) override;

	void setAnimation(std::string name);
	std::string getAnimation() { return m_currentAnimation; };
	void addAnimation(Animation anim,std::string name);
protected:
	sf::Clock m_frameClock;
	sf::Time m_frameTime;

	std::string m_currentAnimation;
	std::map<std::string,std::shared_ptr<Animation>> m_animations;
	AnimatedSprite m_animatedSprite;
};
