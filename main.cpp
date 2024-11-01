#include <SFML/Graphics.hpp> 

#include "Source/PhysicsEngine/SpriteRenderer.h"
#include "Source/PhysicsEngine/ComponentEntityManager.h"
#include <iostream>

void InitialFunction()
{
    RenderManager::GetInstance().window.create(sf::VideoMode(800, 600), "SFML Sprite Example");

    Entity* e =  RenderManager::GetInstance().trackE;
    SpriteRenderer* sr = AddComponent<SpriteRenderer>(e);
    sf::Texture texture;
    if (!texture.loadFromFile("player.png")) {
        return;
    }
    sr->texture = texture;
    e->scaleX =  1.f;
    e->scaleY = 1.f;
    e->xPos = 100.f;
    e->yPos = 100.f;


}

int main() {
    InitialFunction();

    



    while (RenderManager::GetInstance().window.isOpen()) {
        sf::Event event;
        while (RenderManager::GetInstance().window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                RenderManager::GetInstance().window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    
                }
                if (event.key.code == sf::Keyboard::A) {
                    RenderManager::GetInstance().trackE->xPos -= 10;
                }
            }
        }
        RenderManager::GetInstance().Update();
        
        // RenderManager::GetInstance().window.clear();
        // RenderManager::GetInstance().window.draw(circle);
        // RenderManager::GetInstance().window.display();
    }

    return 0;
}