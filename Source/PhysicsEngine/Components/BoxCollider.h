#ifndef _boxcollider_h_
#define _boxcollider_h_

#include "Component.h"
#include "../Entity.h"
#include <functional>
class RigidBody;

class BoxCollider : public Component
{

public:
    BoxCollider(Entity *_entity);
    float width, height;
    std::function<void(BoxCollider *)> OnCollisionEnter, OnCollisionStay, OnCollisionExit, OnColliderLanded, OnHorizontalCollision, OnColliderAbove;
    bool OverlayWith(BoxCollider *collider);
    RigidBody *body;
    friend float CalculateOverlapX(BoxCollider *a, BoxCollider *b);
    friend float CalculateOverlapY(BoxCollider *a, BoxCollider *b);
};

#endif