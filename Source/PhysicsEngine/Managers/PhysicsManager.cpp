#include "PhysicsManager.h"
#include "ColliderManager.h"


PhysicsManager::PhysicsManager()
{

}

PhysicsManager& PhysicsManager::GetInstance()
{
    static PhysicsManager instance;
    return instance;
}

void PhysicsManager::FixedUpdate()
{
    ColliderManager::GetInstance().FixedUpdate();
    for (auto rb : rbList)
    {
        rb->GetOwner()->xPos += rb->xVel * FIXED_TIMESTEP;
        rb->GetOwner()->yPos += rb->yVel * FIXED_TIMESTEP;
    }
}

