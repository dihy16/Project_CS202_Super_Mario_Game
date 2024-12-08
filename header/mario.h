#ifndef MARIO_H
#define MARIO_H
#include "definition.h"
#include <ctime>

class Mario
{
private:
   int stateCounter;
   Clock timer1, timer2, changeStateTimer;
   bool goRight, goLeft, goUp, goDown;
   float acceleration[2], startJumpPosition;
   Area marioArea;
   int mapx, mapy;
   std::clock_t timer;
public:
   Texture marioTexture, marioSuperTexture;
   Sprite marioSprite;
   MarioState marioState;
   bool isJumping, isFalling, isOnGround, powerUpToBig, powerUpToSuper, dead;
   float speed[2];
   hitbox gethixbox()
   {
      return hitbox(mapx, mapy, marioArea.width, marioArea.height);
   }
   // Constructor
   Mario(int x, int y);
   // Draw mario
   void draw(RenderWindow &window, int collisiontag);
   // Handle movement
   void handleEvents(Event &e);
   // Animation
   void animation(RenderWindow &window, int collisiontag);
   // Move
   void move(RenderWindow &window, int collisiontag);
   Position getPosition()
   {
      return Position(mapx, mapy);
   }
   void setRectForWalking(IntRect &rect);
   void standing();
   void jumping(IntRect &rect, int RectPosition, float waitingTime);
   void moveRight(IntRect &rect, RenderWindow &window);
   void moveLeft(IntRect &rect, RenderWindow &window);

private:
   // set to small state
   void smallState();
   // set to big state
   void bigState();
   // set to super state
   void superState();
};

#endif