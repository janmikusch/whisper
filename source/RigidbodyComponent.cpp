#include "stdafx.h"
#include "RigidbodyComponent.h"
#include <xmmintrin.h>
#include "GameEvent.h"
#include "CollisionObserver.h"
#include "Collision.h"
#include <regex>

Rigidbody::Rigidbody(std::shared_ptr<GameObject> parent, float mass, bool useGravity, bool isStatic):Component(parent),m_useGravity(useGravity)
{
	m_mass = mass;
	m_isStatic = isStatic;
	if (mass != 0)
	{
		m_invMass = 1.0f / mass;
	}
	else
	{
		m_invMass = 0;
	}
}


void Rigidbody::update(const float fDeltaTimeSeconds)
{
	if (!m_isStatic)
	{
		sf::Vector2f forces{};

		for (const auto& f : m_forces)
			forces += f;

		for (const auto& i : m_impulses)
			forces += i;
		m_impulses.clear();

		if (m_velocity.y < -1) //when velocity up no longer grounded
		{
			m_isGrounded = false;
		}
		if(!m_isGrounded && m_useGravity)
		{
			forces += m_gravity;
		}

		// symplectic Euler
		m_acceleration = forces * m_invMass;
		m_velocity += m_acceleration * fDeltaTimeSeconds;
		m_velocity = m_velocity * 0.99f; // simple "friction"
		if (m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y < m_minVelocity)
		{
			m_velocity.x = 0.0f;
			m_velocity.y = 0.0f;
		}


		sf::Vector2f movement = m_velocity * fDeltaTimeSeconds * m_speedMultiplier;

		m_parent->move(movement);
	}
}

void Rigidbody::draw(){}

void Rigidbody::init(){}

void Rigidbody::onCollision(Collision collision)
{
	m_collisionsCurrentFrame.push_back(std::make_shared<Collision>(collision));
}

void Rigidbody::onCollisionResolve()
{
	engine::CollisionGameEvent event;

	for(auto collision : m_collisionsCurrentFrame)
	{
		std::shared_ptr<Rigidbody> other;
		std::shared_ptr<Rigidbody> thisRigidbody;
		event.type = engine::CollisionGameEvent::ENTER;
		event.collision = collision;

		if (collision->body1 == std::make_shared<Rigidbody>(*this))
		{
			other = collision->body2;
			thisRigidbody = collision->body1;
		}
		else
		{
			other = collision->body1;
			thisRigidbody = collision->body2;
		}

		for(auto lastCollision : m_collisionsLastFrame)
		{
			if(collision->body1 == lastCollision->body1 && collision->body2 == lastCollision->body2 ||
				collision->body1 == lastCollision->body2 && collision->body2 == lastCollision->body1)
			{
				event.type = engine::CollisionGameEvent::STAY;
				event.collision = lastCollision;
			}
		}

		for (auto observer : m_observers)
		{
			observer->onNotify(other->getGameObject(), std::make_shared<engine::CollisionGameEvent>(event));
			
		}
	}

	//onExit
	for (auto lastCollision : m_collisionsLastFrame)
	{
		std::shared_ptr<Rigidbody> other;
		std::shared_ptr<Rigidbody> ball;
		event.type = engine::CollisionGameEvent::EXIT;

		if (lastCollision->body1 == std::make_shared<Rigidbody>(*this))
		{
			other = lastCollision->body2;
			ball = lastCollision->body1;
		}
		else
		{
			other = lastCollision->body1;
			ball = lastCollision->body2;
		}
		bool found = false; // collision reoccur?
		for (auto collision : m_collisionsCurrentFrame)
		{
			if (lastCollision->body1 == lastCollision->body1 && lastCollision->body2 == lastCollision->body2 ||
				lastCollision->body1 == lastCollision->body2 && lastCollision->body2 == lastCollision->body1)
			{
				found = true;
			}
		}
		if (found == false)
		{
			for (auto observer : m_observers)
			{
				observer->onNotify(other->getGameObject(), std::make_shared<engine::CollisionGameEvent>(event));
			}
		}
	}

	m_collisionsLastFrame.swap(m_collisionsCurrentFrame);
	m_collisionsCurrentFrame.clear();
}


void Rigidbody::addForce(sf::Vector2f force)
{
	m_forces.push_back(force);
}

void Rigidbody::addImpulse(sf::Vector2f force)
{	
	m_impulses.push_back(force);
}

sf::Vector2f Rigidbody::getAcceleration()
{
	return m_acceleration;
}

sf::Vector2f Rigidbody::getVelocity()
{
	return m_velocity;
}

void Rigidbody::setAcceleration(sf::Vector2f acceleration)
{
	m_acceleration = acceleration;
}

void Rigidbody::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

void Rigidbody::addObserver(CollisionObserver& observer)
{
	m_observers.push_back(&observer);
}

void Rigidbody::removeObserver(CollisionObserver& observer)
{
	//auto position = std::find(m_observers.begin(), m_observers.end(), observer);
	//m_observers.erase(position);
}
