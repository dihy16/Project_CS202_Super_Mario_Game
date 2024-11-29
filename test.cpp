#include <SFML/Graphics.hpp> 
#include <SFML/System.hpp>

#include "Source/PhysicsEngine/Managers/ComponentEntityManager.h"
#include "Source/PhysicsEngine/Components/BoxCollider.h"
#include "Source/PhysicsEngine/Components/RigidBody.h"
#include "Source/PhysicsEngine/Components/SpriteRenderer.h"
#include <iostream>






void InitialFunction()
{
    RenderManager::GetInstance().window.create(sf::VideoMode(800, 600), "SFML Sprite Example");

    Entity* e =  RenderManager::GetInstance().trackE;
    e->scaleX =  1.f;
    e->scaleY = 1.f;
    e->xPos = 100.f;
    e->yPos = 100.f;
    SpriteRenderer* sr = AddComponent<SpriteRenderer>(e);
    sr->layer = 1;
    
    sf::Texture texture;
    if (!texture.loadFromFile("Images/TilesBackup.png")) {
        return;
    }
    sr->texture = texture;
    sr->sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    
    BoxCollider* bc =  AddComponent<BoxCollider>(e);
    bc->width = 64.f;
    bc->height = 64.f;
    auto testBoxCollider = [sr](BoxCollider* bc)
    {
        //disappear if the player collides with Bowser
        if (bc->GetOwner()->name == "bowser")
        {
            sr->SetActive(!sr->GetActive());
            
        }
    };
    //bc->OnCollisionEnter = testBoxCollider;
    //ColliderManager::GetInstance().visisbleCollider = true;
    RigidBody* rb = AddComponent<RigidBody>(e);
    bc->body = rb;
    rb->collider = bc;
    rb->isUsingGravity = true;
    //bowser

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
        return;
    }
    sr2->texture = texture2;
    BoxCollider* bc2 = AddComponent<BoxCollider>(bowser);
    bc2->width = 100;
    bc2->height = 100;
    RigidBody* rb2 = AddComponent<RigidBody>(bowser);
    bc2->body = rb2;
    rb2->collider = bc2;
    rb2->isStatic = true;

    //unfinished code for debug console
    sf::Font font;
    if (!font.loadFromFile("resource/Arial.ttf")) {
        return ;
    }
    RenderManager::GetInstance().debugConsole.setString("hello");
    RenderManager::GetInstance().debugConsole.setCharacterSize(12);         // Set character size (in pixels)
    RenderManager::GetInstance().debugConsole.setFillColor(sf::Color::White); // Set text color
    RenderManager::GetInstance().debugConsole.setStyle(sf::Text::Bold);     // 
    RenderManager::GetInstance().debugConsole.setPosition(0, 0);    // 
    RenderManager::GetInstance().displayDebugConsole = true;
}

int main() {
    InitialFunction();


    sf::Clock clock;
    float accumulator = 0.0f;

    

    RigidBody* rb = GetComponent<RigidBody>(RenderManager::GetInstance().trackE);

    while (RenderManager::GetInstance().window.isOpen()) {
        sf::Time dt = clock.restart();
        accumulator += dt.asSeconds();
        
        
        sf::Event event;
        
        while (RenderManager::GetInstance().window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                RenderManager::GetInstance().window.close();
            }
                
            
            
            
        }
         if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            rb->xVel = 0.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            rb->AddForce(-10.f, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            rb->AddForce(10.f, 0.f);
        }
        
        //fixed update
        while (accumulator >= PhysicsManager::FIXED_TIMESTEP)
        {
            PhysicsManager::GetInstance().FixedUpdate();
            accumulator -= PhysicsManager::FIXED_TIMESTEP;
        }

        RenderManager::GetInstance().Update();
  
    }

    return 0;
}