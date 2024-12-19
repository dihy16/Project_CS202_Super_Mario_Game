#ifndef _physicsmanager_h_
#define _physicsmanager_h_

#include "../Components/RigidBody.h"
#include <SFML/System/Clock.hpp>
#include <vector>

class BoxCollider;
class PhysicsManager
{
private:
    PhysicsManager();
    sf::Clock timer;

public:
    static constexpr float FIXED_TIMESTEP = 0.02f;
    PhysicsManager(const PhysicsManager &) = delete;
    PhysicsManager &operator=(const PhysicsManager &) = delete;
    static PhysicsManager &GetInstance();
    void FixedUpdate();
    std::vector<RigidBody *> rbList;
    void ResolveCollision(BoxCollider *a, BoxCollider *b);
};

#endif