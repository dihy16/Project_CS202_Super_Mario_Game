#ifndef _collidermanager_h_
#define _collidermanager_h_

#include "../Components/BoxCollider.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <SFML/System/Clock.hpp>

using std::vector;

class ColliderManager
{
private:
    ColliderManager();
    std::unordered_map<int, vector<int>> collisionMap;

public:
    std::function<void(BoxCollider *, BoxCollider *)> ResolveCollision;
    vector<BoxCollider *> colliderVector;
    bool visibleCollider;
    ColliderManager(const ColliderManager &) = delete;
    ColliderManager &operator=(const ColliderManager &) = delete;
    static ColliderManager &GetInstance();
    void AddCollider(BoxCollider *collider);
    void FixedUpdate();
    bool isGrounded(BoxCollider *collider);
};

#endif