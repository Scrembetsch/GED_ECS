#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

struct Text
{
	static const Component Id = Component::EText;
	sf::Font Font;
	sf::Text Stats;
};