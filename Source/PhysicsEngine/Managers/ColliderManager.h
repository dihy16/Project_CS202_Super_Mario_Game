#ifndef _collidermanager_h_
#define _collidermanager_h_

#include "../Components/BoxCollider.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::vector;

class ColliderManager
{
private:
    ColliderManager();
    std::unordered_map<int, vector<int>> collisionMap;
public:
    vector<BoxCollider*> colliderVector;
    bool visisbleCollider;
    ColliderManager(const ColliderManager&) = delete;
    ColliderManager& operator=(const ColliderManager&) = delete;
    static ColliderManager& GetInstance();
    void AddCollider(BoxCollider* collider);
    void FixedUpdate();
};

#endif