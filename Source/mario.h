#ifndef MARIO_H
#define MARIO_H
#include "./PhysicsEngine/Managers/ComponentEntityManager.h"
#include "./PhysicsEngine/Components/BoxCollider.h"
#include "./PhysicsEngine/Components/RigidBody.h"
#include "./PhysicsEngine/Components/SpriteRenderer.h"
#include "./items.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "marioGameManager.h"
#include "saveGame.h"

#define MARIO "resource/Mario1.png"
#define SUPERMARIO "resource/MarioSuper2.png"
#define BLOCK_WIDTH 64
#define BLOCK_HEIGHT 64
#define MAX_SPEED 1000
#define MIN_SPEED -1000
#define JUMP_FORCE -300

class Item;             // forward declaration
class GameStateMemento; // forward declaration
class Mario : public Entity
{
protected:
   Entity *mario = RenderManager::GetInstance().trackE;

   SpriteRenderer *marioSprite = AddComponent<SpriteRenderer>(mario);
   BoxCollider *marioCollider = AddComponent<BoxCollider>(mario);

   sf::Clock timer1, timer2, timer3, stateTimer, touchTimer;

   enum Direction
   {
      Right,
      Left
   } direction = Right;

public:
   bool goRight, goLeft, goUp, firing, created;
   bool eatMushroom, eatFlower, touchEnemy;
   enum State
   {
      Small,
      Super,
      Fire,
   } state = Small;
   RigidBody *marioRigidBody = AddComponent<RigidBody>(mario);

   Mario(int x, int y);
   void moveRight();
   void moveLeft();
   bool getDirection();
   void setRectForWalking(sf::IntRect &rect);
   void handleMovement();
   void handleEnemy();
   void animation1(float duration, float interval, std::function<void()> onComplete, bool &finished);
   void animation2(float duration, float interval, std::function<void()> onComplete, bool &finished, State &state);
   void handlePowerUp();
   void update(std::vector<std::unique_ptr<Item>> &items);
   void stand();
   GameStateMemento saveState();
   void restoreState(const GameStateMemento &memento);
};

#endif // MARIO_H
