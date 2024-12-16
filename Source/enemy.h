#ifndef ENEMY_H
#define ENEMY_H
#include "./mario.h"
#include <memory>

#define ENEMY "resource/Enemies.png"

class Mario; // forward declaration
class Enemy : public Entity
{
protected:
   bool display, moving, isKilled, onGround, fading;
   bool direction = false;
   sf::Clock timer, movetimer;
   sf::IntRect enemyRect;
   Entity *enemy = new Entity;
   SpriteRenderer *sr = AddComponent<SpriteRenderer>(enemy);
   BoxCollider *bc = AddComponent<BoxCollider>(enemy);
   RigidBody *rb = AddComponent<RigidBody>(enemy);
   int currentRect, maxRect;
   void initialize(int x, int y, sf::IntRect &rect, std::string name);

public:
   Enemy(int x, int y);
   virtual void move() = 0;
   virtual void collideWithMario(Mario &mario) = 0;
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
   void move() override;
   // void kickFromTop(Mario *mario) override;
   // void kickFromBottom(Mario *mario) override;
   // void touchSide(Mario *mario) override;
   void collideWithMario(Mario &mario) override;
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

public:
   Koopa(int x, int y);
   void move() override;
   // void kickFromTop(Mario *mario) override;
   // void kickFromBottom(Mario *mario) override;
   // void touchSide(Mario *mario) override;
   void collideWithMario(Mario &mario) override;
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
   void move() override;
   void throwHammer();
   // void kickFromTop(Mario *mario) override;
   // void kickFromBottom(Mario *mario) override;
   // void touchSide(Mario *mario) override;
   void collideWithMario(Mario &mario) override;
   void fadingAnimation() override;
};

class Hammer : public Enemy
{
private:
   sf::Clock gravityTimer;

public:
   Hammer(int x, int y);
   void move() override;
   // void kickFromTop(Mario *mario) override;
   // void kickFromBottom(Mario *mario) override;
   // void touchSide(Mario *mario) override;
   void collideWithMario(Mario &mario) override;
   void fadingAnimation() override;
};

class PiranhaPlant : public Enemy
{
public:
   PiranhaPlant(int x, int y);
   void move() override;
   // void kickFromTop(Mario *mario) override;
   // void kickFromBottom(Mario *mario) override;
   // void touchSide(Mario *mario) override;
   void collideWithMario(Mario &mario) override;
   void fadingAnimation() override;
};

class EnemyFactory
{
public:
   static std::unique_ptr<Enemy> createEnemy(const std::string &type, int x, int y);
};
#endif