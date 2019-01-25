#pragma once
#include "stdafx.h"
#include "InputComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Layer.h"
#include "RenderComponent.h"


class TextGuiComponent : public RenderComponent, TransformableComponent
{
public:
	explicit TextGuiComponent(std::shared_ptr<GameObject> parent, Layer layer,sf::Text text);

	void update( const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;

	void setPosition(const sf::Vector2f &position) override;
	void setRotation(float angle) override;
	void setScale(const sf::Vector2f& factors) override;
	void setOrigin(const sf::Vector2f &origin) override;
	void move(const sf::Vector2f &movement) override;
	void scale(const sf::Vector2f& factor) override;
	void rotate(float angle) override;

	void setText(sf::Text t);
	void setTextContent(std::string text);

	sf::Text getText() { return m_text; }; 
protected:
	sf::Text m_text;

};
