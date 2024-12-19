#ifndef ITEMS_H
#define ITEMS_H
#include "character.h"
#include <memory>

class Item : public Entity
{
protected:
   bool display, isTaken, fading;
   sf::Clock timer;
   sf::IntRect itemRect;
   SpriteRenderer *sr;
   BoxCollider *bc;
   RigidBody *rb;
   int currentRect, maxRect;
   void initialize(float x, float y, sf::IntRect &rect, std::string name, int maxRect);
   friend class BulletPool;

public:
   Item(int x, int y);
   virtual void animation() = 0;
   virtual void fadeOut() = 0;
};

class Mushroom : public Item
{
public:
   Mushroom(int x, int y);
   void animation() override;
   void fadeOut() override;
};

class Coin : public Item
{
private:
   enum CoinState
   {
      Normal,
      Sparkling
   } state = Normal;
   bool finished = false;

public:
   Coin(int x, int y);
   void setRect();
   void animation() override;
   void fadeOut() override;
};

class Flower : public Item
{
public:
   Flower(int x, int y);
   void animation() override;
   void fadeOut() override;
};

// class Star : public Item
// {
// public:
//    Star(int x, int y);
//    void animation() override;
//    void fadeOut() override;
// };

class Bullet : public Item
{
private:
   sf::Clock fadeTimer, jumpTimer;
   enum State
   {
      Flying,
      Splash
   } state = Flying;
   bool finished = false;
   bool thrown = false;
   bool direction;

public:
   Bullet(int x, int y, bool direction);
   void animation() override;
   void fadeOut() override;
   void reset(int x, int y, bool direction);
   bool isActive() const { return rb->GetActive(); }
   void setActive(bool active)
   {
      rb->SetActive(active);
      bc->SetActive(active);
      sr->SetActive(active);
   }
};

class BulletPool
{
private:
   std::vector<std::unique_ptr<Bullet>> bullets;

public:
   BulletPool(int size);
   Bullet *acquireBullet(int x, int y, bool direction);
   void releaseBullet(Bullet *bullet);
};

class ItemFactory
{
public:
   static BulletPool bulletPool;
   static std::unique_ptr<Item> createItem(const std::string &type, int x, int y, bool direction = false);
};

#endif