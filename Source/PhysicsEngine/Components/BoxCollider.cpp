#include "BoxCollider.h"
BoxCollider::BoxCollider(Entity* _entity) : Component(_entity)
{
    body = nullptr;
}

bool BoxCollider::OverlayWith(BoxCollider* collider)
{
    return
    owner->xPos < collider->owner->xPos + collider->width &&
    owner->xPos + width > collider->owner->xPos &&
    owner->yPos < collider->owner->yPos + collider->height &&
    owner->yPos + height > collider->owner->yPos;
    
}

float CalculateOverlapX(BoxCollider* a, BoxCollider* b) {
    // Calculate the min/max bounds for each collider
    float a_min_x = a->GetOwner()->xPos;
    float a_max_x = a->GetOwner()->xPos + a->width;
    float a_min_y = a->GetOwner()->yPos;
    float a_max_y = a->GetOwner()->yPos + a->height;

    float b_min_x = b->GetOwner()->xPos;
    float b_max_x = b->GetOwner()->xPos + b->width;
    float b_min_y = b->GetOwner()->yPos;
    float b_max_y = b->GetOwner()->yPos + b->height;

    // Calculate overlap along x-axis
    return std::min(a_max_x, b_max_x) - std::max(a_min_x, b_min_x);
}
float CalculateOverlapY(BoxCollider* a, BoxCollider* b) {
    // Calculate the min/max bounds for each collider
    float a_min_x = a->GetOwner()->xPos;
    float a_max_x = a->GetOwner()->xPos + a->width;
    float a_min_y = a->GetOwner()->yPos;
    float a_max_y = a->GetOwner()->yPos + a->height;

    float b_min_x = b->GetOwner()->xPos;
    float b_max_x = b->GetOwner()->xPos + b->width;
    float b_min_y = b->GetOwner()->yPos;
    float b_max_y = b->GetOwner()->yPos + b->height;

    // Calculate overlap along x-axis
    return std::min(a_max_y, b_max_y) - std::max(a_min_y, b_min_y);
}
