#include "RigidBody.h"
#include "../Entity.h"
RigidBody::RigidBody(Entity* _entity) : Component(_entity)
{
    xVel = 0;
    yVel = 0;
    isUsingGravity = false;
    isStatic = false;
    mass = 1.f;
    collider = nullptr;
}

void RigidBody::AddForce(float xForce, float yForce)
{
    if (!isStatic)
    {
        xVel += xForce / mass;
        yVel += yForce / mass;
    }
}