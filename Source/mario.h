#ifndef MARIO_H
#define MARIO_H
#include "./PhysicsEngine/Managers/ComponentEntityManager.h"
#include "./PhysicsEngine/Components/BoxCollider.h"
#include "./PhysicsEngine/Components/RigidBody.h"
#include "./PhysicsEngine/Components/SpriteRenderer.h"
#include "./marioState.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define MARIO "resource/Mario.png"
#define BLOCK_WIDTH 64
#define BLOCK_HEIGHT 64

class Mario : public Entity
{
private:
   Entity *mario = RenderManager::GetInstance().trackE;
   RigidBody *rb = GetComponent<RigidBody>(RenderManager::GetInstance().trackE);

   SpriteRenderer *marioSprite = AddComponent<SpriteRenderer>(mario);
   BoxCollider *marioCollider = AddComponent<BoxCollider>(mario);

   sf::Clock timer1, timer2;
   MarioStateManager stateManager;

public:
   bool goRight, goLeft, goUp;
   RigidBody *marioRigidBody = AddComponent<RigidBody>(mario);

   Mario(int x, int y);
   void moveRight();
   void moveLeft();
   void setRectForWalking(sf::IntRect &rect);
   void handleMovement();
   void handleCollision();
   void handlePowerUp();
   void handleDamage();
};

#endif // MARIO_H