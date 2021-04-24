#pragma once

#include "SFML/Graphics.hpp"
#include "Component.h"

struct Motion
{
	static const Component Id = Component::EMotion;
	sf::Vector2f Velocity;
};