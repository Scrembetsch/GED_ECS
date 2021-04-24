#pragma once

#include <SFML/Graphics.hpp>

struct Text
{
	static const Component Id = Component::EText;
	sf::Font Font;
	sf::Text Stats;
};