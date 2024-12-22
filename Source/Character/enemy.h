#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"

class Character; // forward declaration
class MoveStrategy;
class Enemy : public Entity
{
protected:
   bool display, moving, isKilled, onGround, fading;
   bool direction = false;
   float originX, originY;
   sf::Clock timer, movetimer;
   sf::IntRect enemyRect;
   Entity *enemy = new Entity;
   SpriteRenderer *sr = AddComponent<SpriteRenderer>(enemy);
   BoxCollider *bc = AddComponent<BoxCollider>(enemy);
   RigidBody *rb = AddComponent<RigidBody>(enemy);
   int currentRect, maxRect;
   void initialize(int x, int y, sf::IntRect &rect, std::string name);
   std::unique_ptr<MoveStrategy> moveStrategy;

public:
   Enemy(int x, int y);
   virtual void animation() = 0;
   virtual void collideWithMario(Character &mario) = 0;
   virtual void moveWithMario(Character &mario) = 0;
   virtual void fadingAnimation() = 0;
   // Getter methods to access protected members
   RigidBody *getRigidBody() const { return rb; }
   BoxCollider *getBoxCollider() const { return bc; }
};
class Goomba : public Enemy
{
private:
   enum State
   {
      Normal,
      Cramped,
      Dead
   } state = Normal;
   void setState(State state);

public:
   Goomba(int x, int y);
   void animation() override;
   // void kickFromTop(Mario *mario) override;
   // void kickFromBottom(Mario *mario) override;
   // void touchSide(Mario *mario) override;
   void collideWithMario(Character &mario) override;
   void moveWithMario(Character &mario) override;
   void fadingAnimation() override;
};
class Koopa : public Enemy
{
private:
   enum State
   {
      Normal,
      Jumping,
      Hidden,
      Dead
   } state = Jumping;
   enum Direction
   {
      Left,
      Right
   } direction = Left;
   sf::Clock stateTimer;

public:
   Koopa(int x, int y);
   void animation() override;
   void collideWithMario(Character &mario) override;
   void moveWithMario(Character &mario) override;

   void fadingAnimation() override;
};

class HammerBro : public Enemy
{
private:
   sf::Clock throwTimer;
   bool throwing = false;
   std::unique_ptr<Enemy> hammer = nullptr;

public:
   HammerBro(int x, int y);
   void animation() override;
   void throwHammer();
   void collideWithMario(Character &mario) override;
   void moveWithMario(Character &mario) override;
   void fadingAnimation() override;
};

class Hammer : public Enemy
{
private:
   sf::Clock gravityTimer;

public:
   Hammer(int x, int y);
   void animation() override;
   void collideWithMario(Character &mario) override;
   void moveWithMario(Character &mario) override;
   void fadingAnimation() override;
};

class PiranhaPlant : public Enemy
{
private:
   enum State
   {
      MovingUp,
      WaitingAtTop,
      MovingDown
   } state = MovingUp;
   sf::Clock waitTimer;

public:
   PiranhaPlant(int x, int y);
   void animation() override;
   void collideWithMario(Character &mario) override;
   void moveWithMario(Character &mario) override;

   void fadingAnimation() override;
};

class Gooner : public Enemy
{
private:
   sf::Clock waitTimer;

public:
   Gooner(int x, int y);
   void animation() override;
   void collideWithMario(Character &mario) override;
   void moveWithMario(Character &mario) override;
   void fadingAnimation() override;
};

class EnemyFactory
{
public:
   static std::unique_ptr<Enemy> createEnemy(const std::string &type, int x, int y);
   static void deleteEnemyAtPosition(std::vector<std::unique_ptr<Enemy>> &enemies, int x, int y);
};
#endif