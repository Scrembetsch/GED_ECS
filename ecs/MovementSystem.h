#pragma once

#include "System.h"
#include "SFML/System/Time.hpp"

class MovementSystem : public System
{
public:
	void Update(const sf::Time& dt);
};