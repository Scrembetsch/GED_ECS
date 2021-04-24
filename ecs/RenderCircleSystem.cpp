#include "RenderCircleSystem.h"
#include "Coordinatorh.h"
#include <SFML/System/Vector2.hpp>
#include "TextureManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

extern Coordinator gCoordinator;

void RenderCircleSystem::Render(sf::RenderWindow& window)
{
	const auto& texture = TextureManager::getInstance().getCircleTexture();
	const auto textureSize = static_cast<float>(texture.getSize().x);

	// the texture coordinates
	const sf::Vector2f uvTl(0.f, 0.f);
	const sf::Vector2f uvTr(textureSize, 0.f);
	const sf::Vector2f uvBr(textureSize, textureSize);
	const sf::Vector2f uvBl(0.f, textureSize);

	for (const auto& entity : mEntities)
	{
		const auto& transform = gCoordinator.GetComponent<Transform>(entity);
		const auto& sprite = gCoordinator.GetComponent<Sprite>(entity);


		// generate the corner coordinates
		const sf::Vector2f tl(transform.Position.x - transform.Radius, transform.Position.y - transform.Radius);
		const sf::Vector2f tr(transform.Position.x + transform.Radius, transform.Position.y - transform.Radius);
		const sf::Vector2f bl(transform.Position.x - transform.Radius, transform.Position.y + transform.Radius);
		const sf::Vector2f br(transform.Position.x + transform.Radius, transform.Position.y + transform.Radius);

		// write the vertices (position, color, texture coordinates)
		sf::Vertex vertices[sprite.NumVertices];

		// array pointer for quick iteration
		auto* v = vertices;

		*v++ = sf::Vertex(tl, sprite.Color, uvTl);
		*v++ = sf::Vertex(tr, sprite.Color, uvTr);
		*v++ = sf::Vertex(br, sprite.Color, uvBr);
		*v++ = sf::Vertex(bl, sprite.Color, uvBl);

		// draw using the circle texture
		window.draw(vertices, sprite.NumVertices, sf::Quads, &texture);
	}
}