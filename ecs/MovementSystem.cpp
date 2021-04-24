#include "MovementSystem.h"
#include "Coordinatorh.h"
#include "TransformComponent.h"
#include "MotionComponent.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "VectorMath.h"
#include <algorithm>

extern Coordinator gCoordinator;

void MovementSystem::Update(const sf::Time& dt)
{
	for (const auto& entity : mEntities)
	{
		auto seconds = dt.asSeconds();

		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		const auto& collision = gCoordinator.GetComponent<Collision>(entity);
		auto& motion = gCoordinator.GetComponent<Motion>(entity);

		// Calculate the next position
		auto nextPosition = transform.Position + motion.Velocity * seconds;

		// Check for a potential collision against all bounds
		for (auto bound : collision.Bounds)
		{
			const sf::Vector3f l(bound.first.x, bound.first.y, bound.second - transform.Radius);
			const sf::Vector3f p1(nextPosition.x, nextPosition.y, 1.f);

			const auto distance = VectorMath::dot(p1, l);

			// We have an intersection between circle and boundary
			if (distance <= 0.f)
			{
				const sf::Vector3f p0(transform.Position.x, transform.Position.y, 1.f);
				const sf::Vector3f v(motion.Velocity.x, motion.Velocity.y, 0.f);

				// Calculate the exact time of collision
				const auto t = -VectorMath::dot(l, p0) / VectorMath::dot(l, v);

				// Move the circle forward until it collides
				transform.Position += motion.Velocity * t;

				// Calculate remaining time
				seconds -= t;

				// Invert the movement direction
				const auto reverse = -motion.Velocity;

				// Calculate the reflection vector and take it as the new velocity
				motion.Velocity = 2.f * VectorMath::dot(bound.first, reverse) * bound.first - reverse;

				// For the remaining time, move into the new direction
				nextPosition = transform.Position + motion.Velocity * std::max(seconds, 0.f);

				break;
			}
		}

		transform.Position = nextPosition;
	}
}