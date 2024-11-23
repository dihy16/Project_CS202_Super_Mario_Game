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
            if (a->OverlayWith(b))
            {
                currentCollisions[i].push_back(j);
                currentCollisions[j].push_back(i);
                if (collisionMap[i].empty()
                || std::find(collisionMap[i].begin(), collisionMap[i].end(), j) == collisionMap[i].end()
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
    for (const auto& [id, collidingIds] : collisionMap)
    {
        for (int collidingId: collidingIds)
        {
            BoxCollider* a = colliderVector[id];
            BoxCollider* b = colliderVector[collidingId];
            if (currentCollisions[id].empty()|| std::find(currentCollisions[id].begin(), currentCollisions[id].end(), collidingId) == currentCollisions[id].end())
            {
                if (a->OnCollisionExit)
                {
                    a->OnCollisionExit(b);
                }
                if (b->OnCollisionExit)
                {
                    b->OnCollisionExit(a);
                }
            }
        }
    }
    collisionMap = currentCollisions;
}