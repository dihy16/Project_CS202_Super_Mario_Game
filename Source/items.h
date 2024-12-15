#ifndef ITEMS_H
#define ITEMS_H
#include "./mario.h"
#include <memory>

#define ITEM "resource/Items.png"

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

class Bullet : public Item
{
private:
   sf::Clock fadeTimer;
   enum State
   {
      Flying,
      Splash
   } state = Flying;
   bool finished = false;
   bool thrown = false;

public:
   Bullet(int x, int y);
   void animation() override;
   void fadeOut() override;
};

class ItemFactory
{
public:
   static std::unique_ptr<Item> createItem(const std::string &type, int x, int y);
};

#endif