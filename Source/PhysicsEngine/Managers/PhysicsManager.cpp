#include "PhysicsManager.h"
#include "ColliderManager.h"
#include "Camera.h"
#include "../Components/BoxCollider.h"
#include <algorithm>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "RenderManager.h"
#include "../../Menu/marioGameManager.h"

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
    if (MarioGameManager::getInstance()->getState() == MarioGameManager::GameState::pause)
        return;
    ColliderManager::GetInstance().FixedUpdate();
    for (auto rb : rbList)
    {
        if (!rb->GetActive())
            continue;
        if (ColliderManager::GetInstance().isGrounded(rb->collider))
        {
            if (rb->isJumping && timer.getElapsedTime().asSeconds() > 0.5f)
            {
                if (rb->GetOwner()->tag == "mario")
                    rb->AddForce(0, -500.f);
                else if (rb->GetOwner()->tag == "luigi")
                    rb->AddForce(0, -600.f);
                else if (rb->GetOwner()->name == "enemy")
                    rb->AddForce(0, -300.f);
                else if (rb->GetOwner()->name == "fireball")
                    rb->AddForce(0, -200.f);
                rb->isFlying = true;
                rb->isJumping = false;
                timer.restart();
            }
            else
            {
                rb->yVel = 0;
            }
        }
        else if (rb->isUsingGravity)
        {
            rb->AddForce(0, 10.0f);
        }
        if (rb->GetOwner()->name == "character")
        {
            if (rb->GetOwner()->yPos + (rb->yVel * FIXED_TIMESTEP) < 0)
            {
                rb->GetOwner()->yPos = 0;
                rb->AddForce(0, 10.0f);
            }
        }
        rb->GetOwner()->xPos += (rb->xVel * FIXED_TIMESTEP);
        rb->GetOwner()->yPos += (rb->yVel * FIXED_TIMESTEP);
    }
}

void PhysicsManager::ResolveCollision(BoxCollider *a, BoxCollider *b)
{
    // RenderManager::GetInstance().debugText += "hit";

    if (a->body == nullptr || b->body == nullptr)
        return;
    RigidBody *rbA = a->body;
    RigidBody *rbB = b->body;

    float overlapX = CalculateOverlapX(a, b);
    float overlapY = CalculateOverlapY(a, b);
    if ((a->GetOwner()->name == "Block" || b->GetOwner()->name == "Block") || (rbA->isStatic && rbB->isStatic))
        return;
    if (overlapX < overlapY)
    {

        // Resolve the collision along the X axis
        if (a->GetOwner()->xPos > b->GetOwner()->xPos)
        {
            // Push `a` to the right of `b`
            a->GetOwner()->xPos += overlapX;
            if (a->OnHorizontalCollision)
            {
                a->OnHorizontalCollision(b);
            }
            if (b->OnHorizontalCollision)
            {
                b->OnHorizontalCollision(a);
            }
        }
        else
        {
            // Push `a` to the left of `b`
            a->GetOwner()->xPos -= overlapX;
            if (a->OnHorizontalCollision)
            {
                a->OnHorizontalCollision(b);
            }
            if (b->OnHorizontalCollision)
            {
                b->OnHorizontalCollision(a);
            }
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
            if (a->OnColliderLanded)
            {

                a->OnColliderLanded(b);
            }
            if (b->OnColliderAbove)
            {
                b->OnColliderAbove(a);
            }
        }
        else
        {
            // Push `a` below `b`
            a->GetOwner()->yPos -= overlapY;
            if (b->OnColliderLanded)
            {

                b->OnColliderLanded(a);
            }
            if (a->OnColliderAbove)
            {
                a->OnColliderAbove(b);
            }
        }

        // Adjust velocities for Y direction
        if (a->body && b->body)
        {

            a->body->yVel = 0;
            b->body->yVel = 0;
        }
    }
}