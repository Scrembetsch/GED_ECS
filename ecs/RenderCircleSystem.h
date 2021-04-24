#pragma once

#include "System.h"
#include <SFML/Graphics/RenderWindow.hpp>

class RenderCircleSystem : public System
{
public:
	void Render(sf::RenderWindow& window);
};