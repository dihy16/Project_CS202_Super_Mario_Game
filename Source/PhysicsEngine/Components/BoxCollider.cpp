#include "BoxCollider.h"
BoxCollider::BoxCollider(Entity* _entity) : Component(_entity)
{
    
}

bool BoxCollider::OverlayWith(BoxCollider* collider)
{
    return
    owner->xPos < collider->owner->xPos + collider->width &&
    owner->xPos + width > collider->owner->xPos &&
    owner->yPos < collider->owner->yPos + collider->height &&
    owner->yPos + height > collider->owner->yPos;
    
}