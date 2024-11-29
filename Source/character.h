#pragma once

#include "definition.h"

class Character
{
private:
   int x, y; // coordinates, w.r.t. map
   Texture normal, super;
   Sprite activesprite;
   MarioState marioState;
   Area marioArea;
   float speed[2];
   bool goUp, goLeft, goRight, onGround;
   Clock timer1, timer2;
   IntRect marioRect = activesprite.getTextureRect();

public:
   Character(int x, int y);
   void draw(RenderWindow &window);
   void keycheck();
   void handlemovement();
   void animation();
   // void move();
   void moveLeft();
   void moveRight();
   void jumpUp();
   void setRectForWalking(IntRect &rect);
   Position getScreenPositon();

private:
   void smallState();
};