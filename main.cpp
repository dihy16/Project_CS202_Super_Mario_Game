#include "./Source/mario.h"
#include "./Source/enemy.h"
#include "./Source/items.h"
#include "./Source/map.h"
#include "./Source/marioGameManager.h"

int main()
{
    // InitialFunction();
    Mario mario(100, 100);
    Map m("Data/maps.txt");
    m.blockgenerator(100, 12 * BLOCK_HEIGHT);

    RenderManager::GetInstance().window.create(sf::VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "SFML Sprite Example");
    sf::Font font;
    if (!font.loadFromFile("resource/Arial.ttf"))
    {
    }
    RenderManager::GetInstance().debugConsole.setFont(font);
    RenderManager::GetInstance().debugConsole.setString("lmao");
    RenderManager::GetInstance().debugConsole.setCharacterSize(12);           // Set character size (in pixels)
    RenderManager::GetInstance().debugConsole.setFillColor(sf::Color::White); // Set text color
    RenderManager::GetInstance().debugConsole.setStyle(sf::Text::Bold);       //
    RenderManager::GetInstance().debugConsole.setPosition(0, 0);              //
    RenderManager::GetInstance().displayDebugConsole = true;
    sf::Clock clock;
    float accumulator = 0.0f;
    ColliderManager::GetInstance().visisbleCollider = true;

    MarioGameManager::getInstance()->playMusic("overworld");

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
        mario.goLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        mario.goRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        mario.marioRigidBody->isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

        m.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        m.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

        // mario.handleMovement();
        // if (mario.goLeft)
        //     m.moveleft(-mario.marioRigidBody->xVel);
        // else if (mario.goRight)
        //     m.moveright(mario.marioRigidBody->xVel);

        if (m.left == m.right)
            ;
        else if (m.left)
            m.moveleft(2);
        else if (m.right)
            m.moveright(2);

        // for (auto &enemy : enemies)
        //     enemy->move();

        // for (auto &item : items)
        //     item->animation();
        // fixed update
        while (accumulator >= PhysicsManager::FIXED_TIMESTEP)
        {
            PhysicsManager::GetInstance().FixedUpdate();
            accumulator -= PhysicsManager::FIXED_TIMESTEP;
        }
        RenderManager::GetInstance().window.clear();
        MarioGameManager::getInstance()->draw(RenderManager::GetInstance().window);
        RenderManager::GetInstance().window.display();
    }

    return 0;
}