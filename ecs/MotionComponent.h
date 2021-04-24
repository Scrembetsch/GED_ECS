#pragma once

#include "SFML/Graphics.hpp"

struct Motion
{
	static const Component Id = Component::EMotion;
	sf::Vector2f Velocity;
};