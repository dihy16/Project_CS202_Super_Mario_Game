#ifndef _physicsmanager_h_
#define _physicsmanager_h_

class BoxCollider;
#include "../Components/RigidBody.h"
#include <vector>

class PhysicsManager
{
private:
    PhysicsManager();
public:
    static constexpr float FIXED_TIMESTEP = 0.02f;
    PhysicsManager(const PhysicsManager&)  = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;
    static PhysicsManager& GetInstance();
    void FixedUpdate();
    std::vector<RigidBody*> rbList;
    void ResolveCollision(BoxCollider* a, BoxCollider* b);
};

#endif