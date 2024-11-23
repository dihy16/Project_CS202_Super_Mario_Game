#include "RigidBody.h"
RigidBody::RigidBody(Entity* _entity) : Component(_entity)
{
    xVel = 0;
    yVel = 0;
    isUsingGravity = false;
    myBoxCollider = nullptr;
}