#pragma once

#include <vector>
#include <utility>

#include "SFML/Graphics.hpp"

struct Collision
{
	std::vector<std::pair<sf::Vector2f, float>> Bounds;
};