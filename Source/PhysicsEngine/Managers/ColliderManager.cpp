#include "ColliderManager.h"
#include "RenderManager.h"

ColliderManager::ColliderManager()
{
    visibleCollider = true;
}

ColliderManager &ColliderManager::GetInstance()
{
    static ColliderManager instance;
    return instance;
}

void ColliderManager::AddCollider(BoxCollider *collider)
{
    colliderVector.push_back(collider);
}

void ColliderManager::FixedUpdate()
{
    std::unordered_map<int, std::vector<int>> currentCollisions;
    // check for collision

    for (int i = 0; i < colliderVector.size(); i++)
    {
        BoxCollider *a = colliderVector[i];
        if (!a->GetActive())
            continue;

        for (int j = i + 1; j < colliderVector.size(); j++)
        {
            BoxCollider *b = colliderVector[j];
            if (!b->GetActive())
                continue;
            int aID = a->GetOwner()->getID();
            int bID = b->GetOwner()->getID();
            if (a->OverlayWith(b))
            {
                currentCollisions[aID].push_back(bID);
                currentCollisions[bID].push_back(aID);
                if (collisionMap[aID].empty() || std::find(collisionMap[aID].begin(), collisionMap[aID].end(), bID) == collisionMap[aID].end())
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

bool ColliderManager::isGrounded(BoxCollider *collider)
{
    if (!collider->GetActive())
        return false;

    for (int id : collisionMap[collider->GetOwner()->getID()])
    {
        BoxCollider *other = nullptr;
        for (auto col : colliderVector)
        {
            if (col->GetOwner()->getID() == id)
            {
                other = col;
            }
        }
        if (other && other->GetActive())
        {
            float maxA = collider->GetOwner()->yPos + collider->height;
            float minB = other->GetOwner()->yPos;
            float maxB = minB + other->height;
            if (minB < maxA && maxA < maxB)
            {
                if ((collider->GetOwner()->name == "Turret" || collider->GetOwner()->name == "MushroomTile" || collider->GetOwner()->name == "Flag" || collider->GetOwner()->name == "Pipe" || collider->GetOwner()->name == "FloatingBlock" || collider->GetOwner()->name == "MysteryBox" || collider->GetOwner()->name == "EmptyBox") && (other->GetOwner()->name == "character" || other->GetOwner()->name == "enemy"))
                {
                    return true;
                }
                if (collider->GetOwner()->name == "character")
                {
                    collider->GetOwner()->yPos = other->GetOwner()->yPos - collider->height;
                    return true;
                }
                collider->GetOwner()->yPos = other->GetOwner()->yPos - collider->height + 1;
                return true;
            }
        }
    }
    return false;
}