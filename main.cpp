#include "./Source/Menu/marioGameManager.h"
#include "./Source/PhysicsEngine/Managers/Camera.h"
#include "./Source/Menu/saveGame.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define DIV 1048576

int main()
{
    bool resuming = false;
    // MarioGameManager m1;
    // Map &gameMap = lv1.getMap();
    // Mario &mario = lv1.getMario();
    // if (resuming)
    // {
    //     RenderManager::GetInstance().debugText = "Resuming game";
    //     GameStateMemento memento = GameStateMemento::loadState("log/game_state.txt");
    //     mario.restoreState(memento);
    // }
    // else
    //     RenderManager::GetInstance().debugText = "Starting new game";

    MEMORYSTATUSEX statex;
    GlobalMemoryStatusEx(&statex);

    RenderManager::GetInstance().window.create(sf::VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "SFML Sprite Example");
    sf::Font font;
    if (!font.loadFromFile("resource/Arial.ttf"))
    {
    }
    RenderManager::GetInstance().window.setFramerateLimit(60);
    RenderManager::GetInstance().debugConsole.setFont(font);
    RenderManager::GetInstance().debugConsole.setString(std::to_string(statex.dwMemoryLoad));
    RenderManager::GetInstance().debugConsole.setCharacterSize(12);         // Set character size (in pixels)
    RenderManager::GetInstance().debugConsole.setFillColor(sf::Color::Red); // Set text color
    RenderManager::GetInstance().debugConsole.setStyle(sf::Text::Bold);     //
    RenderManager::GetInstance().debugConsole.setPosition(0, 0);            //
    RenderManager::GetInstance().displayDebugConsole = true;
    sf::Clock clock;
    float accumulator = 0.0f;
    ColliderManager::GetInstance().visibleCollider = false;

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
        Camera::GetInstance().posX = RenderManager::GetInstance().trackE->xPos - 200;
        // RenderManager::GetInstance().debugText = std::to_string(Camera::GetInstance().posX);

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                // Camera::GetInstance().posX -= Camera::CAMERA_MOVE_SPPED;
                RenderManager::GetInstance().debugText = std::to_string(Camera::GetInstance().posX);
            }
            if (event.key.code == sf::Keyboard::Right)
            {
                // Camera::GetInstance().posX += Camera::CAMERA_MOVE_SPPED;
                RenderManager::GetInstance().debugText = std::to_string(Camera::GetInstance().posX);
            }
        }
        // fixed update
        while (accumulator >= PhysicsManager::FIXED_TIMESTEP)
        {
            PhysicsManager::GetInstance().FixedUpdate();
            accumulator -= PhysicsManager::FIXED_TIMESTEP;
            MarioGameManager::getInstance()->updateGameState(static_cast<int>(PhysicsManager::FIXED_TIMESTEP * 1000), event);
        }
        RenderManager::GetInstance().window.clear();
        // m.draw(RenderManager::GetInstance().window);
        MarioGameManager::getInstance()->draw(RenderManager::GetInstance().window);
        RenderManager::GetInstance().window.display();
    }
    // GameStateMemento memento = mario.saveState();
    // saveGame(memento, "log/game_state.txt");
    return 0;
}