#pragma once

#include <vector>
#include <utility>
#include "Component.h"
#include "SFML/Graphics.hpp"

struct Collision
{
	static const Component Id = Component::ECollision;
	std::vector<std::pair<sf::Vector2f, float>> Bounds;
};