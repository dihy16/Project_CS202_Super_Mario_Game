#include "./Source/mario.h"
#include "./Source/enemy.h"
#include "./Source/items.h"
#include "./Source/map.h"

int main()
{
    // InitialFunction();
    Mario mario(100, 100);
    // Map m;
    // m.blockgenerator(mario.xPos, mario.yPos);
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Item>> items;

     enemies.push_back(EnemyFactory::createEnemy("Goomba", 200, 100));
    enemies.push_back(EnemyFactory::createEnemy("Koopa", 300, 100));
    //enemies.push_back(EnemyFactory::createEnemy("HammerBro", 400, 100));
    // enemies.push_back(EnemyFactory::createEnemy("PiranhaPlant", 500, 100));
    // items.push_back(ItemFactory::createItem("Mushroom", 200, 100));
    // items.push_back(ItemFactory::createItem("Coin", 300, 100));
    // items.push_back(ItemFactory::createItem("Sparkle", 400, 100));
    // items.push_back(ItemFactory::createItem("Flower", 500, 100));
    
    Entity* bowser = new Entity;
    RenderManager::GetInstance().listEntity.push_back(bowser);
    
    bowser->scaleX = 1.f;
    bowser->scaleY = 1.f;
    bowser->xPos = 100;
    bowser->yPos = 500;
    bowser->name = "bowser";
    SpriteRenderer* sr2 = AddComponent<SpriteRenderer>(bowser);
    sr2->layer = 0;
    
    sf::Texture texture2;
    if (!texture2.loadFromFile("resource/bowser.png")) {
        //return;
    }
    sr2->texture = texture2;
    BoxCollider* bc2 = AddComponent<BoxCollider>(bowser);
    bc2->width = 500;
    bc2->height = 100;
    RigidBody* rb2 = AddComponent<RigidBody>(bowser);
    bc2->body = rb2;
    rb2->collider = bc2;
    rb2->isStatic = true;

    RenderManager::GetInstance().window.create(sf::VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "SFML Sprite Example");
    sf::Font font;
    if (!font.loadFromFile("resource/Arial.ttf")) {

    }
    RenderManager::GetInstance().debugConsole.setFont(font);
    // RenderManager::GetInstance().debugConsole.setString("hello");
    RenderManager::GetInstance().debugText = "nothing yet";
    RenderManager::GetInstance().debugConsole.setCharacterSize(12);         // Set character size (in pixels)
    RenderManager::GetInstance().debugConsole.setFillColor(sf::Color::White); // Set text color
    RenderManager::GetInstance().debugConsole.setStyle(sf::Text::Bold);     // 
    RenderManager::GetInstance().debugConsole.setPosition(0, 0);    // 
    RenderManager::GetInstance().displayDebugConsole = true;
    sf::Clock clock;
    float accumulator = 0.0f;
    ColliderManager::GetInstance().visisbleCollider = true;
    
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
        mario.marioRigidBody->isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        // if (mario.goRight == mario.goLeft)
        // {
        // mario.marioRigidBody->xVel = 0;
        // }
        // else if (mario.goRight)
        // {
        // mario.moveRight();
        
        // }
        // else if (mario.goLeft)
        // {
        // mario.moveLeft();
        
        // }
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