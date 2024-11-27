#include "definition.h"

class Mario
{
private:
   int stateCounter;
   Clock timer1, timer2, changeStateTimer;
   bool goRight, goLeft, goUp, goDown;
   float acceleration[2], startJumpPosition;
   Area marioArea;
   int mapx, mapy;

public:
   Texture marioTexture, marioSuperTexture;
   Sprite marioSprite;
   MarioState marioState;
   bool isJumping, isFalling, isOnGround, powerUpToBig, powerUpToSuper, dead;
   float speed[2];
   hitbox gethixbox()
   {
      // move the origin from middle leg to top left corner
      return hitbox(mapx - 1.5 * marioArea.width / 2, mapy - 1.5 * marioArea.height, marioArea.width, marioArea.height);
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
   Position getSurroundingPosition();
   void setRectForWalking(IntRect &rect);
   void standing();
   void jumping(IntRect &rect, int RectPosition, float waitingTime);
   void moveRight(IntRect &rect, RenderWindow &window);
   void moveLeft(IntRect &rect, RenderWindow &window);
   void adjustposition(int collisiontag);
private:
   // set to small state
   void smallState();
   // set to big state
   void bigState();
   // set to super state
   void superState();
};