#pragma once

#include <SFML/Graphics.hpp>

struct Text
{
	static const ComponentType Id = Component::EText;
	sf::Font Font;
	sf::Text Stats;
};