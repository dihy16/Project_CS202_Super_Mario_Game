#include "./Source/mario.h"
#include "./Source/enemy.h"
#include "./Source/items.h"
#include "./Source/map.h"

int main()
{
    // InitialFunction();
    Mario mario(100, 100);
    Map m;
    m.blockgenerator(mario.xPos, mario.yPos);
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Item>> items;

    // enemies.push_back(EnemyFactory::createEnemy("Goomba", 200, 100));
    // enemies.push_back(EnemyFactory::createEnemy("Koopa", 300, 100));
    enemies.push_back(EnemyFactory::createEnemy("HammerBro", 400, 700));
    // enemies.push_back(EnemyFactory::createEnemy("PiranhaPlant", 500, 100));
    //  items.push_back(ItemFactory::createItem("Mushroom", 200, 100));
    //  items.push_back(ItemFactory::createItem("Coin", 300, 100));
    //  items.push_back(ItemFactory::createItem("Sparkle", 400, 100));
    //  items.push_back(ItemFactory::createItem("Flower", 500, 100));

    RenderManager::GetInstance().window.create(sf::VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "SFML Sprite Example");
    sf::Clock clock;
    float accumulator = 0.0f;
    ColliderManager::GetInstance().visisbleCollider = true;

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
        mario.marioRigidBody->isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

        mario.handleMovement();
        for (auto &enemy : enemies)
            enemy->move();

        for (auto &item : items)
            item->animation();
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