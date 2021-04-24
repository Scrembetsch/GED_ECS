#pragma once

#include <vector>
#include <utility>
#include "Component.h"
#include "SFML/Graphics.hpp"

struct Collision
{
	static const ComponentType Id = Component::ECollision;
	std::vector<std::pair<sf::Vector2f, float>> Bounds;
};