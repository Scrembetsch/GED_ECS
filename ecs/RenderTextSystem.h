#pragma once

#include "System.h"
#include "SFML/System/Time.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class RenderTextSystem : public System
{
public:
	void Update(const sf::Time& dt);
	void Render(sf::RenderWindow& window);
};