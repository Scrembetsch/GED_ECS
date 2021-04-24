#pragma once

#include "SFML/Graphics.hpp"

struct Transform
{

	static const Component Id = Component::ETransform;

	sf::Vector2f Position;
	float Radius;
};