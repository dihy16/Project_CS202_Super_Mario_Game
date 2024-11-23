#ifndef _rigidbody_h_
#define _rigidbody_h_

#include "BoxCollider.h"

class RigidBody : public Component
{
public:
    RigidBody(Entity* _entity);
    float xVel, yVel;
    bool isUsingGravity;
    BoxCollider* myBoxCollider;
};

#endif