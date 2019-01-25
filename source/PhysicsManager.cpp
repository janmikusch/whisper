#include "stdafx.h"
#include "PhysicsManager.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BallInputComponent.h"
#include "BoundingBoxComponent.h"
#include "TextGuiComponent.h"
#include "ScoreComponent.h"
#include "GameOverComponent.h"
#include "ScoreManager.h"
#include "GameEvent.h"

bool PhysicsManager::AABBvsAABB(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal,
                                float& penetration)
{
	auto getCenter = [](const sf::FloatRect& rect) -> sf::Vector2f
	{
		return sf::Vector2f(rect.left, rect.top) + 0.5f * sf::Vector2f(rect.width, rect.height);
	};

	sf::Vector2f n = getCenter(b) - getCenter(a);
	float a_extent = a.width * 0.5f; // Calculate half extents along x axis
	float b_extent = b.width * 0.5f;
	float x_overlap = a_extent + b_extent - abs(n.x); // Calculate overlap on x axis

	if (x_overlap > 0)
	{
		float a_extent = a.height * 0.5f; // Calculate half extents along y axis
		float b_extent = b.height * 0.5f;
		float y_overlap = a_extent + b_extent - abs(n.y); // Calculate overlap on y axis 

		if (y_overlap > 0)
		{
			// Find out which axis is axis of least penetration
			if (x_overlap < y_overlap)
			{
				// Point towards B knowing that n points from A to B
				if (n.x < 0)
					normal = sf::Vector2f(1.0f, 0.0f);
				else
					normal = sf::Vector2f(-1.0f, 0.0f);
				penetration = x_overlap;
			}
			else
			{
				// Point towards B knowing that n points from A to B
				if (n.y < 0)
					normal = sf::Vector2f(0, 1);
				else
					normal = sf::Vector2f(0, -1);
				penetration = y_overlap;
			}
			return true;
		}
	}
	return false;
}

void PhysicsManager::findCollisions(std::vector<std::shared_ptr<GameObject>> gameObjects)
{
	int i = 0;
	for (auto itA = gameObjects.begin(); itA != gameObjects.end(); ++itA)
	{
		i++;
		auto& body1 = *itA;

		if (body1->getComponent<ColliderComponent>() == nullptr)
			continue;
		int j = i;
		for (auto itB = itA; itB != gameObjects.end(); ++itB)
		{
			j++;
			if (itA == itB)
				continue;

			auto& body2 = *itB;

			if (body2->getComponent<ColliderComponent>() == nullptr)
				continue;

			// if both object don't have a mass or body is the same skip
			if (body1->getComponent<Rigidbody>()->getMass() == 0 && body2->getComponent<Rigidbody>()->getMass() == 0)
				continue;

			sf::Transform body1Transform;
			body1Transform.translate(body1->getPosition());
			sf::Transform body2Transform;
			body2Transform.translate(body2->getPosition());
			sf::Vector2f normal;
			float penetration;

			auto shape1 = body1->getComponent<ColliderComponent>()->getShape();
			auto shape2 = body2->getComponent<ColliderComponent>()->getShape();

			bool test = AABBvsAABB(shape1,
			                       shape2,
			                       normal,
			                       penetration);

			if (test)
			{
				Collision manifold;
				manifold.body1 = body1->getComponent<Rigidbody>();
				manifold.body2 = body2->getComponent<Rigidbody>();
				manifold.normal = normal;
				manifold.penetration = penetration;

#ifdef _DEBUG
				body1->getComponent<BoundingboxComponent>()->setColor(sf::Color::Green);
				body2->getComponent<BoundingboxComponent>()->setColor(sf::Color::Blue);
#endif // _DEBUG


				if (body1->getComponent<ColliderComponent>()->isTrigger())
				{
					body2->getComponent<Rigidbody>()->onCollision(manifold);
				}
				else
				{
					m_manifolds.push_back(manifold);
				}
			}
		}
		body1->getComponent<Rigidbody>()->onCollisionResolve();
	}

	resolveCollisions();
	m_manifolds.clear();
}

void PhysicsManager::resolveCollisions()
{
	for (auto man : m_manifolds)
	{
		// Calculate relative velocity
		sf::Vector2f rv = man.body1->getVelocity() - man.body2->getVelocity();

		// Calculate relative velocity in terms of the normal direction (length through vector projection)
		float velAlongNormal = rv.x * man.normal.x + rv.y * man.normal.y;

		// Do not resolve if velocities are separating
		if (velAlongNormal > 0)
			return;

		if(velAlongNormal > -0.09)
		{
			man.body1->setGrounded(true);
			man.body2->setGrounded(true);
			man.body1->setVelocity(sf::Vector2f{man.body1->getVelocity().x,0});
			man.body2->setVelocity(sf::Vector2f{ man.body1->getVelocity().x,0 });
			return;
		}

		const bool restitutionOn = true;
		if (restitutionOn)
		{
			// Calculate impulse scalar
			const float e =	0.99f; //< 1.0 = all objects are bouncy
			float j = -(1 + e) * velAlongNormal;
			j /= man.body1->getInvMass() + man.body2->getInvMass();

			// Apply impulse
			sf::Vector2f impulse = j * man.normal;

			// impulse proportional to mass
			man.body1->setVelocity(man.body1->getVelocity() + impulse * man.body1->getInvMass());
			man.body2->setVelocity(man.body2->getVelocity() - impulse * man.body2->getInvMass());

			//err() << "velAlongNormal " << velAlongNormal << " impulse " << impulse.x << " " << impulse.y << endl;
		}
		else
		{
			// Apply impulse

			sf::Vector2f impulse = velAlongNormal * man.normal;
			man.body1->setVelocity(-0.5f * impulse);
			man.body2->setVelocity(0.5f * impulse);
		}

		// Positional correction
		const bool positionalCorrection = true;
		if (positionalCorrection)
		{
			const float percent = 0.2f; // usually 20% to 80%
			const float slop = 0.01f; // usually 0.01 to 0.1
			sf::Vector2f correction = std::max(man.penetration - slop, 0.0f) /
				(man.body1->getInvMass() + man.body2->getInvMass()) * percent * man.normal;
			// Apply directly to position
			if (!man.body1->isStatic())
			{
				man.body1->getGameObject().move(man.body1->getInvMass() * correction);
			}
			if (!man.body2->isStatic())
			{
				man.body2->getGameObject().move(man.body2->getInvMass() * correction);
			}
		}
	}
}
