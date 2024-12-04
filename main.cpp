#include "./Source/mario.h"
#include "./Source/enemy.h"

int main()
{
    // InitialFunction();
    Mario mario(100, 100);
    std::vector<std::unique_ptr<Enemy>> enemies;

    // enemies.push_back(EnemyFactory::createEnemy("Goomba", 200, 100));
    // enemies.push_back(EnemyFactory::createEnemy("Koopa", 300, 100));
    enemies.push_back(EnemyFactory::createEnemy("HammerBro", 400, 100));

    // enemies.push_back(EnemyFactory::createEnemy("PiranhaPlant", 500, 100));

    for (auto &enemy : enemies)
    {
        if (HammerBro *hammerBro = dynamic_cast<HammerBro *>(enemy.get()))
        {
            hammerBro->throwHammer(enemies);
        }
    }
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

        mario.handleMovement();
        for (auto &enemy : enemies)
        {

            enemy->move();
        }

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