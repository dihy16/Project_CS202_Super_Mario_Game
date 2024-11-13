#include "../header/mario.h"

Mario::Mario(float x, float y)
{
   acceleration[0] = 25, acceleration[1] = 40;
   speed[0] = 0, speed[1] = 0;
   goRight = goLeft = goUp = goDown = false;
   isJumping = false;
   isOnGround = true;
   startJumpPosition = 500;

   marioTexture.loadFromFile(MARIO);
   marioSuperTexture.loadFromFile(MARIO_SUPER);
   marioTexture.setSmooth(true);
   marioSuperTexture.setSmooth(true);
   marioSprite.setTexture(marioTexture);
   marioSprite.setPosition(x, y);
   marioSprite.setScale(1.5, 1.5);

   smallState();
}

void Mario::draw(RenderWindow &window)
{
   window.draw(marioSprite);
   animation(window);
}

void Mario::animation(RenderWindow &window)
{
   move(window);
}

void Mario::smallState()
{
   marioSprite.setTexture(marioTexture);
   marioState = MarioState::SMALL;
   marioArea.width = 28;
   marioArea.height = 32;
   marioSprite.setTextureRect(IntRect(0, 96, marioArea.width, marioArea.height));
   marioSprite.setOrigin(marioArea.width / 2, marioArea.height);
}

void Mario::bigState()
{
   marioSprite.setTexture(marioTexture);
   marioState = MarioState::BIG;
   marioArea.width = 32;
   marioArea.height = 60;
   marioSprite.setTextureRect(IntRect(0, 36, marioArea.width, marioArea.height));
   marioSprite.setOrigin(marioArea.width / 2, marioArea.height);
}

void Mario::superState()
{
   bigState();
   marioState = MarioState::SUPER;
   marioSprite.setTexture(marioSuperTexture);
}

void Mario::handleEvents(Event &e)
{
   switch (e.type)
   {
   case Event::KeyPressed:
      switch (e.key.code)
      {
      case Keyboard::Right:
      case Keyboard::D:
         goRight = true;
         break;
      case Keyboard::Left:
      case Keyboard::A:
         goLeft = true;
         break;
      case Keyboard::Up:
      case Keyboard::W:
         goUp = true;
         break;
      case Keyboard::Down:
      case Keyboard::S:
         goDown = true;
         break;
      }
      break;
   case Event::KeyReleased:
      switch (e.key.code)
      {
      case Keyboard::Right:
      case Keyboard::D:
         goRight = false;
         speed[0] = 0;
         break;
      case Keyboard::Left:
      case Keyboard::A:
         goLeft = false;
         speed[0] = 0;
         break;
      case Keyboard::Up:
      case Keyboard::W:
         goUp = false;
         break;
      case Keyboard::Down:
      case Keyboard::S:
         goDown = false;
         break;
      }
      break;
   }
}

void Mario::setRectForWalking(IntRect &rect)
{
   int maxLeft = 0, picWidth = 0;
   if (marioState == MarioState::SMALL)
   {
      maxLeft = 99;
      picWidth = 33;
   }
   else if (marioState == MarioState::BIG || marioState == MarioState::SUPER)
   {
      maxLeft = 96;
      picWidth = 32;
   }

   if (rect.left >= maxLeft)
      rect.left = picWidth;
   else
      rect.left += picWidth;
}

void Mario::jumping(IntRect &rect, int RectPosition, float waitingTime)
{
   if (isOnGround)
   {
      isJumping = false;
      speed[1] = 0;
   }
   else
   {
      if (speed[1] > 0)
         acceleration[1] = 200;
      else
         acceleration[1] = 120;

      speed[1] += acceleration[1] * waitingTime;
      // Check if Mario has landed
      if (marioSprite.getPosition().y > startJumpPosition)
      {
         marioSprite.setPosition(marioSprite.getPosition().x, startJumpPosition);
         isOnGround = true;
         speed[1] = 0;
         isJumping = false;
      }
   }
}

void Mario::moveRight(IntRect &rect, RenderWindow &window)
{
   if (speed[0] <= -1)
      rect.left = 130;
   else
      setRectForWalking(rect);
   if (!isJumping)
      marioSprite.setTextureRect(rect);
   marioSprite.setScale(1.5, 1.5);

   if (window.getSize().x - marioSprite.getPosition().x - marioArea.width / 2 < 0)
      marioSprite.setPosition(window.getSize().x - marioArea.width / 2, marioSprite.getPosition().y);
   if (marioSprite.getPosition().x == window.getSize().x - marioArea.width / 2)
   {
      speed[0] = 0;
      acceleration[0] = 0;
   }
   else
      speed[0] = 25;
   // if (acceleration[0] > 0)
   //    acceleration[0] *= -1;
}

void Mario::moveLeft(IntRect &rect, RenderWindow &window)
{
   if (speed[0] >= 1)
      rect.left = 130;
   else
      setRectForWalking(rect);
   if (!isJumping)
      marioSprite.setTextureRect(rect);
   marioSprite.setScale(-1.5, 1.5);

   if (marioSprite.getPosition().x - marioArea.width / 2 < 0)
      marioSprite.setPosition(0, marioSprite.getPosition().y);
   if (marioSprite.getPosition().x == 0)
      speed[0] = 0;
   else
      speed[0] = -25;
   // if (acceleration[0] < 0)
   //    acceleration[0] *= -1;
}

void Mario::standing()
{
   speed[0] = 0;
   switch (marioState)
   {
   case MarioState::SMALL:
      smallState();
      break;
   case MarioState::BIG:
      bigState();
      break;
   case MarioState::SUPER:
      superState();
      break;
   default:
      break;
   }
}

void Mario::move(RenderWindow &window)
{
   if (isOnGround)
      isJumping = false;
   IntRect marioRect = marioSprite.getTextureRect();
   float waitingTime = 0.05;
   if (timer1.getElapsedTime().asSeconds() > waitingTime)
   {
      // jump when press arrow up
      int jumpRectPosition = 160;
      if (goUp)
      {
         marioRect.left = jumpRectPosition;
         marioSprite.setTextureRect(marioRect);
         if (!isJumping)
         {
            isJumping = true;
            isOnGround = false;
            startJumpPosition = marioSprite.getPosition().y;
            speed[1] = -60;
         }
         goUp = false;
      }
      jumping(marioRect, jumpRectPosition, waitingTime);
      waitingTime += 0.05;
      if (timer2.getElapsedTime().asSeconds() > waitingTime)
      {
         if (goRight)
            moveRight(marioRect, window);
         else if (goLeft)
            moveLeft(marioRect, window);
         else
         {
            // acceleration movement when release keyboard
            if (speed[0] >= 1 || speed[0] <= -1)
            {
               setRectForWalking(marioRect);
               if (!isJumping)
                  marioSprite.setTextureRect(marioRect);
               speed[0] += acceleration[0] * waitingTime;
            }
         }
         if (goDown)
            goDown = false;

         timer2.restart();
      }
      marioSprite.move(speed[0], speed[1]);
      timer1.restart();
   }
   if (speed[0] < 1 && speed[0] > -1 && isOnGround)
      standing();
}
