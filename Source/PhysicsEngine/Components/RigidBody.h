#ifndef _rigidbody_h_
#define _rigidbody_h_

#include "Component.h"

class BoxCollider;


class RigidBody : public Component
{
public:
    RigidBody(Entity* _entity);
    float xVel, yVel, mass;
    bool isUsingGravity, isStatic;
    BoxCollider* collider;
    void AddForce(float xForce, float yForce);
};

#endif