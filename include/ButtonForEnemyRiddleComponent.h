#pragma once
#include "stdafx.h"
#include "InputComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Layer.h"
#include "RenderComponent.h"
#include "CollisionObserver.h"
#include "Room.h"
#include "Color.h"
#include "ButtonComponent.h"


class ButtonForEnemyRiddleComponent : public ButtonComponent
{
public:
	explicit ButtonForEnemyRiddleComponent(std::shared_ptr<GameObject> parent, Layer layer, sf::Texture& texture, engine::Color c, int id);

	void onNotify(const GameObject& collidedWith, std::shared_ptr<engine::GameEvent> event) override;
	void update(const float fDeltaTimeSeconds) override;
	void init() override;

protected:
	sf::Sprite m_buttonPressed;
	sf::Sprite m_buttonReleased;
	sf::Sprite m_currentState;
	engine::Color m_color;
	bool m_isPressed = false; 
	int m_id; 
	float m_timer = 0.0f;
	std::vector<std::shared_ptr<GameObject>> m_enemies;
	std::vector<std::shared_ptr<GameObject>>::iterator nextEnemy;

	bool enemiesLoaded;
};
