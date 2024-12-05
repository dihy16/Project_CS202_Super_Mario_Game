#include "RenderManager.h"
#include <iostream>

RenderManager::RenderManager()
{
    trackE = new Entity();
    displayDebugConsole = false;
  

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
    //sort by 
    for (int i = 0; i < 15; i++)
    {
        for (SpriteRenderer* sr : srVector)
        {
            if (sr->layer == i && sr->GetActive())
            {
                sr->sprite.setTexture(sr->texture);
                sr->sprite.setPosition(sr->GetOwner()->xPos, sr->GetOwner()->yPos);
                sr->sprite.setRotation(sr->GetOwner()->rotation);
                sr->sprite.setScale(sr->GetOwner()->scaleX, sr->GetOwner()->scaleY);
                window.draw(sr->sprite);
            }
            
            
        }
    }
    if (ColliderManager::GetInstance().visisbleCollider)
    {
        for (auto collider: ColliderManager::GetInstance().colliderVector)
        {
            sf::RectangleShape rectangle(sf::Vector2(collider->width, collider->height));
            rectangle.setPosition(collider->GetOwner()->xPos, collider->GetOwner()->yPos );
            rectangle.setOutlineColor(sf::Color::Red);
            rectangle.setOutlineThickness(5.0f);
            rectangle.setFillColor(sf::Color::Transparent);
            window.draw(rectangle);
        }
    }
    if (displayDebugConsole)
    {
        debugConsole.setString(debugText);
        window.draw(debugConsole);
    }
    
    window.display();
}

