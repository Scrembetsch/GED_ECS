#include <SFML/Graphics.hpp>

#include "Coordinatorh.h"
#include "TransformComponent.h"
#include "MotionComponent.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "MovementSystem.h"
#include "RenderCircleSystem.h"
#include "RenderTextSystem.h"
#include "RandomNumberGenerator.h"
#include "ColorPicker.h"

Coordinator gCoordinator;

int main()
{
    const unsigned int windowWidth = 1024;
    const unsigned int windowHeight = 768;
    // const unsigned int numEntities = 52500;  // Anja
    const unsigned int numEntities = 170000;    // Harald
    //const unsigned int numEntities = 10;
    const sf::Rect<float> bounds(0.f, 0.f, windowWidth, windowHeight);
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ECS Moving Circles");

    gCoordinator.Init();

    gCoordinator.RegisterComponent<Transform>();
    gCoordinator.RegisterComponent<Motion>();
    gCoordinator.RegisterComponent<Collision>();
    gCoordinator.RegisterComponent<Sprite>();
    gCoordinator.RegisterComponent<Text>();

    auto movementSystem = gCoordinator.RegisterSystem<MovementSystem>();
    {
        Signature sig;
        sig.set(gCoordinator.GetComponentType<Transform>());
        sig.set(gCoordinator.GetComponentType<Motion>());
        sig.set(gCoordinator.GetComponentType<Collision>());
        gCoordinator.SetSystemSignature<MovementSystem>(sig);
    }

    auto renderCircleSystem = gCoordinator.RegisterSystem<RenderCircleSystem>();
    {
        Signature sig;
        sig.set(gCoordinator.GetComponentType<Transform>());
        sig.set(gCoordinator.GetComponentType<Sprite>());
        gCoordinator.SetSystemSignature<RenderCircleSystem>(sig);
    }

    auto renderTextSystem = gCoordinator.RegisterSystem<RenderTextSystem>();
    {
        Signature sig;
        sig.set(gCoordinator.GetComponentType<Text>());
        gCoordinator.SetSystemSignature<RenderTextSystem>(sig);
    }

    std::vector<Entity> entities(numEntities);

    for (auto& entity : entities)
    {
        auto& rng = RandomNumberGenerator::getInstance();

        // create the entity with random color, radius, and velocity
        // always start from center position
        Transform transform;
        transform.Position.x = (bounds.left + bounds.width) / 2.f;
        transform.Position.y = (bounds.top + bounds.height) / 2.f;
        transform.Radius = rng.generateFloat(8.f, 32.f);

        Sprite sprite;
        sprite.Color = ColorPicker::generateRandomColor();

        Motion motion;
        const auto twoPi = static_cast<float>(atan(1.0) * 4 * 2);
        const auto angle = rng.generateFloat(0.f, twoPi);
        const auto v = rng.generateFloat(5.f, 100.f);
        motion.Velocity.x = cos(angle) * v;
        motion.Velocity.y = sin(angle) * v;

        Collision collision;
        collision.Bounds = {
            std::make_pair(sf::Vector2f(0.f, 1.f), bounds.top),
            std::make_pair(sf::Vector2f(-1.f, 0.f), bounds.left + bounds.width),
            std::make_pair(sf::Vector2f(0.f, -1.f), bounds.top + bounds.height),
            std::make_pair(sf::Vector2f(1.f, 0.f), bounds.left)
        };

        entity = gCoordinator.CreateEntity();
        gCoordinator.AddComponent<Transform>(entity, transform);
        gCoordinator.AddComponent<Collision>(entity, collision);
        gCoordinator.AddComponent<Sprite>(entity, sprite);
        gCoordinator.AddComponent<Motion>(entity, motion);
    }

    Entity stats = gCoordinator.CreateEntity();
    Text text;
    text.Font.loadFromFile("fonts/JetBrainsMono-Regular.ttf");
    text.Stats.setFont(text.Font);
    text.Stats.setCharacterSize(24);
    text.Stats.setFillColor(sf::Color::Yellow);
    gCoordinator.AddComponent<Text>(stats, text);
    entities.push_back(stats);

    sf::Clock clock;
    while (window.isOpen())
    {
        const auto dt = clock.restart();

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        movementSystem->Update(dt);
        renderTextSystem->Update(dt);

        window.clear();

        renderCircleSystem->Render(window);
        renderTextSystem->Render(window);

        window.display();
    }

    entities.clear();
    return 0;
}
