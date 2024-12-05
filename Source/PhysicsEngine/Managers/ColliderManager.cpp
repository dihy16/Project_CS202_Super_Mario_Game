#include "ColliderManager.h"

ColliderManager::ColliderManager()
{
    visisbleCollider = false;
}

ColliderManager& ColliderManager::GetInstance()
{
    static ColliderManager instance;
    return instance;
}

void ColliderManager::AddCollider(BoxCollider* collider)
{
    colliderVector.push_back(collider);
}


void ColliderManager::FixedUpdate()
{
    std::unordered_map<int, std::vector<int>> currentCollisions;
    for (int i = 0; i < colliderVector.size(); i++)
    {
        for (int j = i + 1; j < colliderVector.size(); j++)
        {
            BoxCollider* a = colliderVector[i];
            BoxCollider* b = colliderVector[j];
            int aID = a->GetOwner()->getID();
            int bID = b->GetOwner()->getID();
            if (a->OverlayWith(b))
            {
                currentCollisions[aID].push_back(bID);
                currentCollisions[bID].push_back(aID);
                if (collisionMap[aID].empty()
                || std::find(collisionMap[aID].begin(), collisionMap[aID].end(), bID) == collisionMap[aID].end()
                )
                {
                    if (a->OnCollisionEnter)
                    {
                        a->OnCollisionEnter(b);
                    }
                    if (b->OnCollisionEnter)
                    {
                        b->OnCollisionEnter(a);
                    }
                    if (ResolveCollision)
                    {
                        ResolveCollision(a, b);
                    }
                }
                else 
                {
                    if (a->OnCollisionStay)
                    {
                        a->OnCollisionStay(b);
                    }
                    if (b->OnCollisionStay)
                    {
                        b->OnCollisionStay(a);
                    }
                }
            }
        }
    }
    // for (const auto& [id, collidingIds] : collisionMap)
    // {
    //     for (int collidingId: collidingIds)
    //     {
    //         BoxCollider* a = colliderVector[id];
    //         BoxCollider* b = colliderVector[collidingId];
    //         if (currentCollisions[id].empty()|| std::find(currentCollisions[id].begin(), currentCollisions[id].end(), collidingId) == currentCollisions[id].end())
    //         {
    //             if (a->OnCollisionExit)
    //             {
    //                 a->OnCollisionExit(b);
    //             }
    //             if (b->OnCollisionExit)
    //             {
    //                 b->OnCollisionExit(a);
    //             }
    //         }
    //     }
    // }
    collisionMap = currentCollisions;
}

bool ColliderManager::isGrounded(BoxCollider* collider)
{
    for (int id : collisionMap[collider->GetOwner()->getID()])
    {
        BoxCollider* other = nullptr;
        for (auto col : colliderVector)
        {
            if (col->GetOwner()->getID() == id)
            {
                other = col;
            }
        }
        if (other)
        {
            float maxA = collider->GetOwner()->yPos + collider->height;
            float minB = other->GetOwner()->yPos;
            float maxB = minB + other->height;
            if (minB < maxA && maxA < maxB)
            {
                return true;
            }
        }
    }
    return false;
}