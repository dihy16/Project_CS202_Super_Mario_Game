#include "./Source/level1.h"
#include "./Source/marioGameManager.h"
#include "./Source/PhysicsEngine/Managers/Camera.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define DIV 1048576

int main()
{
    // InitialFunction();
    Level1 lv1;
    // Mario mario(100, 100);
    //bool left, right;
    //Map m("Data/Level1");
    //m.blockgenerator(100, 12 * BLOCK_HEIGHT);
    MEMORYSTATUSEX statex;
    GlobalMemoryStatusEx (&statex);
    // std::vector<std::unique_ptr<Enemy>> enemies;
    // std::vector<std::unique_ptr<Item>> items;

    // enemies.push_back(EnemyFactory::createEnemy("Goomba", 200, 100));
    // enemies.push_back(EnemyFactory::createEnemy("Koopa", 300, 100));
    // enemies.push_back(EnemyFactory::createEnemy("HammerBro", 400, 700));
    // enemies.push_back(EnemyFactory::createEnemy("PiranhaPlant", 500, 100));
    //  items.push_back(ItemFactory::createItem("Mushroom", 200, 100));
    //  items.push_back(ItemFactory::createItem("Coin", 300, 100));
    //  items.push_back(ItemFactory::createItem("Sparkle", 400, 100));
    //  items.push_back(ItemFactory::createItem("Flower", 500, 100));

    RenderManager::GetInstance().window.create(sf::VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "SFML Sprite Example");
    sf::Font font;
    if (!font.loadFromFile("resource/Arial.ttf"))
    {
    }
    RenderManager::GetInstance().debugConsole.setFont(font);
    RenderManager::GetInstance().debugConsole.setString(std::to_string(statex.dwMemoryLoad));
    RenderManager::GetInstance().debugConsole.setCharacterSize(12);           // Set character size (in pixels)
    RenderManager::GetInstance().debugConsole.setFillColor(sf::Color::Red); // Set text color
    RenderManager::GetInstance().debugConsole.setStyle(sf::Text::Bold);       //
    RenderManager::GetInstance().debugConsole.setPosition(0, 0);              //
    RenderManager::GetInstance().displayDebugConsole = true;
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
            MarioGameManager::getInstance()->handleEvents(RenderManager::GetInstance().window, event);
        }
        lv1.execute();

        // if (mario.goLeft)
        //     m.moveleft(-mario.marioRigidBody->xVel);
        // else if (mario.goRight)
        //     m.moveright(mario.marioRigidBody->xVel);

        // if (m.left && m.right)
        //     ;
        // else if (m.left)
        //     m.moveleft(2);
        // else if (m.right)
        //     m.moveright(2);
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                Camera::GetInstance().posX -= Camera::CAMERA_MOVE_SPPED;
                RenderManager::GetInstance().debugText = std::to_string(Camera::GetInstance().posX);
            }
            if (event.key.code == sf::Keyboard::Right)
            {
                Camera::GetInstance().posX += Camera::CAMERA_MOVE_SPPED;
                RenderManager::GetInstance().debugText = std::to_string(Camera::GetInstance().posX);
            }
        }
        // fixed update
        while (accumulator >= PhysicsManager::FIXED_TIMESTEP)
        {
            PhysicsManager::GetInstance().FixedUpdate();
            accumulator -= PhysicsManager::FIXED_TIMESTEP;
            MarioGameManager::getInstance()->updateGameState(static_cast<int>(PhysicsManager::FIXED_TIMESTEP * 1000));
        }
        RenderManager::GetInstance().window.clear();
        //m.draw(RenderManager::GetInstance().window);
        lv1.drawLevel();
        MarioGameManager::getInstance()->draw(RenderManager::GetInstance().window);
        RenderManager::GetInstance().window.display();
    }
    return 0;
}