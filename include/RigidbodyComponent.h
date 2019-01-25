#pragma once
#include "stdafx.h"
#include "Component.h"
#include <list>
#include <SFML/Graphics/RectangleShape.hpp>
#include "CollisionObserver.h"


class CollisionObserver;
struct Collision;

class Rigidbody : public Component
{
public:
	Rigidbody(std::shared_ptr<GameObject> parent, float mass = 0, bool useGravity = false, bool isStatic = true);
	void update(const float fDeltaTimeSeconds) override;
	void draw() override;
	void init() override;

	void onCollision(Collision collision);
	void onCollisionResolve();
	void addForce(sf::Vector2f force);
	void addImpulse(sf::Vector2f force);	

	sf::Vector2f getAcceleration();
	sf::Vector2f getVelocity();
	void setAcceleration(sf::Vector2f acceleration);
	void setVelocity(sf::Vector2f velocity);

	void addObserver(CollisionObserver& observer);
	void removeObserver(CollisionObserver& observer);

	float getMass() { return m_mass; };
	float getInvMass() { return m_invMass; };
	bool isStatic() { return m_isStatic; }
	void setGrounded(bool isGrounded) { m_isGrounded = isGrounded; };
private:
	float m_mass;
	float m_invMass;
	bool m_useGravity = true;
	const sf::Vector2f m_gravity{ 0.0f, 9.f };
	const float m_speedMultiplier = 100.0f;
	const float m_minVelocity = 0.0001f;
	bool m_isStatic = true;
	bool m_isGrounded = false;

	std::list<sf::Vector2f> m_forces{};
	std::list<sf::Vector2f> m_impulses{};

	sf::Vector2f m_acceleration;
	sf::Vector2f m_velocity;

	std::vector<CollisionObserver*> m_observers;

	std::vector<std::shared_ptr<Collision>> m_collisionsCurrentFrame;
	std::vector<std::shared_ptr<Collision>> m_collisionsLastFrame;
};
