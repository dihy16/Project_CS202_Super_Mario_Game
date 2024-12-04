#ifndef ENEMY_H
#define ENEMY_H
#include "./mario.h"
#include <memory>

#define ENEMY "resource/Enemies.png"

class Enemy : public Entity
{
protected:
   bool display, moving, isKilled, onGround, fading;
   sf::Clock timer;
   sf::IntRect enemyRect;
   sf::Sprite enemySprite;
   SpriteRenderer *sr;
   BoxCollider *bc;
   RigidBody *rb;
   int currentRect, maxRect;
   void initialize(int x, int y, sf::IntRect &rect, std::string name);

public:
   Enemy(int x, int y);
   virtual void move() = 0;
   // Getter methods to access protected members
   RigidBody *getRigidBody() const { return rb; }
   BoxCollider *getBoxCollider() const { return bc; }
};
class Goomba : public Enemy
{
public:
   Goomba(int x, int y);
   void move() override;
};
class Koopa : public Enemy
{
public:
   Koopa(int x, int y);
   void move() override;
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
};

class Hammer : public Enemy
{
private:
   sf::Clock gravityTimer;

public:
   Hammer(int x, int y);
   void move();
};

class PiranhaPlant : public Enemy
{
public:
   PiranhaPlant(int x, int y);
   void move() override;
};

class EnemyFactory
{
public:
   static std::unique_ptr<Enemy> createEnemy(const std::string &type, int x, int y);
};
#endif