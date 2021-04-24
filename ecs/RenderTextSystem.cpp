#include "RenderTextSystem.h"
#include "Coordinatorh.h"
#include "TextComponent.h"
#include "SFML/System/Time.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

extern Coordinator gCoordinator;

void RenderTextSystem::Update(const sf::Time& dt)
{
	for (const auto& entity : mEntities)
	{
		auto& text = gCoordinator.GetComponent<Text>(entity);
		const auto frametime = "frametime: " + std::to_string(dt.asMilliseconds()) + " ms";
		text.Stats.setString(frametime);
	}
}

void RenderTextSystem::Render(sf::RenderWindow& window)
{
	for (const auto& entity : mEntities)
	{
		const auto& text = gCoordinator.GetComponent<Text>(entity);
		window.draw(text.Stats);
	}
}