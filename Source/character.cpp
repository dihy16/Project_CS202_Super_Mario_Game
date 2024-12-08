#include "../header/character.h"

Character::Character(int x, int y)
{
   this->x = x;
   this->y = y;
   speed[0] = 0, speed[1] = 0;
   goLeft = goRight = goUp = false;
   onGround = true;
   normal.loadFromFile(MARIO);
   super.loadFromFile(MARIO_SUPER);
   normal.setSmooth(true);
   super.setSmooth(true);
   activesprite.setTexture(normal);
   activesprite.setPosition(x, y);
   activesprite.setScale(1.5, 1.5);
   smallState();
}

Position Character::getScreenPositon()
{
   return Position(x - 3 * BLOCK_WIDTH, y);
}

void Character::keycheck()
{
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      goRight = true;
   else
      goRight = false;
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      goLeft = true;
   else
      goLeft = false;
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      goUp = true;
   else
      goUp = false;
}

void Character::handlemovement()
{

   float waitingTime = 0.05;
   if (timer1.getElapsedTime().asSeconds() > waitingTime)
   {
      // if (goUp)
      //    jump();
      waitingTime += 0.05;
      if (timer2.getElapsedTime().asSeconds() > waitingTime)
      {
         if (goLeft == goRight)
         {
            speed[0] = 0;
            setRectForWalking(marioRect);
         }
         else if (goLeft)
            moveLeft();
         else if (goRight)
            moveRight();

         timer2.restart();
      }
      activesprite.move(speed[0], speed[1]);
      x += speed[0];
      y += speed[1];
      timer1.restart();
   }
}

void Character::draw(RenderWindow &w)
{
   animation();
   activesprite.setPosition(getScreenPositon().x, getScreenPositon().y);
   w.draw(activesprite);
}

void Character::animation()
{
   marioRect = activesprite.getTextureRect();
   activesprite.setTextureRect(marioRect);
}

void Character::smallState()
{
   activesprite.setTexture(normal);
   marioState = MarioState::SMALL;
   marioArea.width = 32;
   marioArea.height = 32;
   activesprite.setTextureRect(IntRect(0, 96, marioArea.width, marioArea.height));
   activesprite.setOrigin(marioArea.width / 2, marioArea.height);
}

void Character::moveLeft()
{
   if (speed[0] >= 1)
      marioRect.left = 130;
   // else
   //    setRectForWalking(marioRect);
   speed[0] = -25;
   activesprite.setScale(-1.5, 1.5);
}

void Character::moveRight()
{
   if (speed[0] <= -1)
      marioRect.left = 130;
   speed[0] = 25;
   activesprite.setScale(1.5, 1.5);
}

void Character::jumpUp()
{
   if (onGround)
   {
      speed[1] = 0;
      goUp = false;
   }
   else
   {
      speed[1] = -25;
   }
}

void Character::setRectForWalking(IntRect &rect)
{
   int maxLeft = 0, picWidth = 0;
   if (marioState == MarioState::SMALL)
   {
      maxLeft = 99;
      picWidth = 33;
   }

   if (rect.left >= maxLeft)
      rect.left = picWidth;
   else
      rect.left += picWidth;
}