#include "RenderManager.h"
#include <iostream>
#include "Camera.h"

RenderManager::RenderManager()
{
    trackE = new Entity();
    displayDebugConsole = false;
}

RenderManager &RenderManager::GetInstance()
{
    static RenderManager instance;
    return instance;
}

void RenderManager::AddSpriteRenderer(SpriteRenderer *sr)
{
    srVector.push_back(sr);
}

void RenderManager::Update()
{
    // window.clear();
    // sort by
    for (int i = 0; i < 15; i++)
    {
        for (SpriteRenderer *sr : srVector)
        {
            if (sr->layer == i && sr->GetActive())
            {
                float newPosX = sr->GetOwner()->xPos - Camera::GetInstance().posX;
                float newPosY = sr->GetOwner()->yPos - Camera::GetInstance().posY;

                if (sr->GetOwner()->name != "mario")
                {
                    if (newPosX < -64 || newPosX > window.getSize().x + 64 || newPosY < -64 || newPosY > window.getSize().y + 64)
                        continue;
                    sr->sprite.setTexture(sr->texture);
                    sr->sprite.setPosition(newPosX, newPosY);
                }
                else
                {
                    sr->sprite.setTexture(sr->texture);
                    sr->sprite.setPosition(sr->GetOwner()->xPos, sr->GetOwner()->yPos);
                }
                sr->sprite.setRotation(sr->GetOwner()->rotation);
                sr->sprite.setScale(sr->GetOwner()->scaleX, sr->GetOwner()->scaleY);
                window.draw(sr->sprite);
            }
        }
    }
    if (ColliderManager::GetInstance().visisbleCollider)
    {
        for (auto collider : ColliderManager::GetInstance().colliderVector)
        {
            if (!collider->GetActive())
                continue;
            sf::RectangleShape rectangle(sf::Vector2(collider->width, collider->height));
            float newPosX = collider->GetOwner()->xPos - Camera::GetInstance().posX;
            float newPosY = collider->GetOwner()->yPos - Camera::GetInstance().posY;

            if (collider->GetOwner()->name != "mario")
            {
                if (newPosX < -64 || newPosX > window.getSize().x + 64 || newPosY < -64 || newPosY > window.getSize().y + 64)
                    continue;
                rectangle.setPosition(newPosX, newPosY);
            }
            else
                rectangle.setPosition(collider->GetOwner()->xPos, collider->GetOwner()->yPos);
            rectangle.setOutlineColor(sf::Color::Red);
            rectangle.setOutlineThickness(2.0f);
            rectangle.setFillColor(sf::Color::Transparent);
            window.draw(rectangle);
        }
    }
    if (displayDebugConsole)
    {
        debugConsole.setString(debugText);
        window.draw(debugConsole);
    }

    // window.display();
}
