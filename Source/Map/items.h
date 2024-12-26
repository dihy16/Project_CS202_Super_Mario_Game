#ifndef ITEMS_H
#define ITEMS_H
#include "./../Character/character.h"
#include <memory>

class Item : public Entity
{
protected:
   bool display, isTaken, isMoving = false;
   sf::Clock timer, dropTimer;
   sf::IntRect itemRect;
   SpriteRenderer *sr;
   BoxCollider *bc;
   RigidBody *rb;
   int currentRect, maxRect;
   void initialize(float x, float y, sf::IntRect &rect, std::string name, int maxRect);

public:
   bool isTouch = false;
   Item(int x, int y);
   virtual void animation() = 0;
   virtual void fadeOut() = 0;
   RigidBody *getRigidBody() const { return rb; }
   SpriteRenderer *getSpriteRenderer() const { return sr; }
   BoxCollider *getBoxCollider() const { return bc; }
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
   int tempRect = 0;

public:
   Coin(int x, int y);
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
   bool direction;

public:
   Bullet(int x, int y, bool direction);
   void animation() override;
   void fadeOut() override;
};

class Princess : public Item
{
public:
   Princess(int x, int y);
   void animation() override;
   void fadeOut() override;
};

class ItemFactory
{
public:
   static std::unique_ptr<Item> createItem(const std::string &type, int x, int y, bool direction = false);
   static void deleteItemAtPosition(std::vector<std::unique_ptr<Item>> &items, int x, int y);
};

#endif