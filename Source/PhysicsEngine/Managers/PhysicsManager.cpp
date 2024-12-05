#include "PhysicsManager.h"
#include "ColliderManager.h"
#include "../Components/BoxCollider.h"
#include <algorithm>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "RenderManager.h"

using sf::Vector2f;

PhysicsManager::PhysicsManager()
{
    ColliderManager::GetInstance().ResolveCollision = [this](BoxCollider *bc1, BoxCollider *bc2)
    { ResolveCollision(bc1, bc2); };
}

PhysicsManager &PhysicsManager::GetInstance()
{
    static PhysicsManager instance;
    return instance;
}

void PhysicsManager::FixedUpdate()
{
    ColliderManager::GetInstance().FixedUpdate();
    for (auto rb : rbList)
    {
        if (ColliderManager::GetInstance().isGrounded(rb->collider))
        {
            if (rb->isJumping)
            {
                rb->AddForce(0, -300.f);
                rb->isJumping = false;
            }
            else
            {
                rb->yVel = 0;
            }
        }
        else if (rb->isUsingGravity)
        {
            rb->AddForce(0, 9.8f);
        }

        rb->GetOwner()->xPos += rb->xVel * FIXED_TIMESTEP;
        rb->GetOwner()->yPos += rb->yVel * FIXED_TIMESTEP;
    }
}

void PhysicsManager::ResolveCollision(BoxCollider *a, BoxCollider *b)
{
    RenderManager::GetInstance().debugText += "hit";

    if (a->body == nullptr || b->body == nullptr)
        return;
    RigidBody *rbA = a->body;
    RigidBody *rbB = b->body;

    float overlapX = CalculateOverlapX(a, b);
    float overlapY = CalculateOverlapY(a, b);
    if (rbA->isStatic && rbB->isStatic)
        return;

    if (overlapX < overlapY)
    {

        // Resolve the collision along the X axis
        if (a->GetOwner()->xPos > b->GetOwner()->xPos)
        {
            // Push `a` to the right of `b`
            a->GetOwner()->xPos += overlapX;
        }
        else
        {
            // Push `a` to the left of `b`
            a->GetOwner()->xPos -= overlapX;
        }

        // Adjust velocities based on the resolution
        if (a->body && b->body)
        {

            a->body->xVel = -a->body->xVel * (1.0f / 3.0f);
            b->body->xVel = -b->body->xVel * (1.0f / 3.0f);
        }
    }
    else
    {
        // Resolve the collision along the Y axis
        if (a->GetOwner()->yPos > b->GetOwner()->yPos)
        {
            // Push `a` above `b`
            a->GetOwner()->yPos += overlapY;
        }
        else
        {
            // Push `a` below `b`
            a->GetOwner()->yPos -= overlapY;
        }

        // Adjust velocities for Y direction
        if (a->body && b->body)
        {

            a->body->yVel = 0; // Reflect the velocity
            b->body->yVel = 0;
        }
    }
}