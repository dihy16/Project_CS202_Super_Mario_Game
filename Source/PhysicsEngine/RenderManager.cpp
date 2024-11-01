#include "RenderManager.h"

RenderManager::RenderManager()
{
    trackE = new Entity();
}

RenderManager& RenderManager::GetInstance()
{
    static RenderManager instance;
    return instance;
}

void RenderManager::AddSpriteRenderer(SpriteRenderer* sr)
{
    srVector.push_back(sr);
}

void RenderManager::Update()
{
    window.clear();
    // sf::Sprite s;
    // sf::Texture t;
    // t.loadFromFile("player.png");
    // s.setTexture(t);
    // s.setPosition(100.f, 100.f);
    // window.draw(s);
    for (SpriteRenderer* sr : srVector)
    {

        
        sr->sprite.setTexture(sr->texture);
        sr->sprite.setPosition(sr->GetOwner()->xPos, sr->GetOwner()->yPos);
        sr->sprite.setRotation(sr->GetOwner()->rotation);
        sr->sprite.setScale(sr->GetOwner()->scaleX, sr->GetOwner()->scaleY);
        window.draw(sr->sprite);
        // sf::CircleShape circle(50); // Radius of 50
        // circle.setFillColor(sf::Color::Green); // Set circle color
        // circle.setPosition(175, 275); // Center the circle initially
        // window.draw(circle);
    }
    window.display();
}