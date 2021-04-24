#pragma once

#include "SFML/Graphics.hpp"

struct Sprite
{
	static const Component Id = Component::ESprite;
	sf::Color Color;
	static const size_t NumVertices = 4;
};