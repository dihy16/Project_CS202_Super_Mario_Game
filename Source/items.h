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
   void initialize(int x, int y, sf::IntRect &rect, std::string name, int maxRect);

public:
   Item(int x, int y);
   virtual void animation() = 0;
};

class Mushroom : public Item
{
public:
   Mushroom(int x, int y);
   void animation() override;
};

class Coin : public Item
{
public:
   Coin(int x, int y);
   void animation() override;
};

class Sparkle : public Item
{
public:
   Sparkle(int x, int y);
   void animation() override;
};

class Flower : public Item
{
public:
   Flower(int x, int y);
   void animation() override;
};

class ItemFactory
{
public:
   static std::unique_ptr<Item> createItem(const std::string &type, int x, int y);
};

#endif