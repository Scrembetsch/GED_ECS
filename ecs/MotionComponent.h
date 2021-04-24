#pragma once

#include "SFML/Graphics.hpp"

struct Motion
{
	static const ComponentType Id = Component::EMotion;
	sf::Vector2f Velocity;
};