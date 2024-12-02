#include "./Source/test_mario.h"

int main()
{
    // InitialFunction();
    Mario mario(100, 100);
    RenderManager::GetInstance().window.create(sf::VideoMode(800, 600), "SFML Sprite Example");

    sf::Clock clock;
    float accumulator = 0.0f;

    // RigidBody *rb = GetComponent<RigidBody>(RenderManager::GetInstance().trackE);

    while (RenderManager::GetInstance().window.isOpen())
    {
        sf::Time dt = clock.restart();
        accumulator += dt.asSeconds();

        sf::Event event;

        while (RenderManager::GetInstance().window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                RenderManager::GetInstance().window.close();
            }
        }
        mario.goLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        mario.goRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        mario.goUp = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

        // mario.handleMovement();

        // fixed update
        while (accumulator >= PhysicsManager::FIXED_TIMESTEP)
        {
            PhysicsManager::GetInstance().FixedUpdate();
            accumulator -= PhysicsManager::FIXED_TIMESTEP;
        }

        RenderManager::GetInstance().Update();
    }

    return 0;
}