#include "mario.h"

Mario::Mario(int x, int y)
{
   // RenderManager::GetInstance().listEntity.push_back(mario);
   goRight = goLeft = goUp = false;

   mario->scaleX = 1.5;
   mario->scaleY = 1.5;
   mario->xPos = x;
   mario->yPos = y;

   marioSprite->layer = 1;
   marioSprite->texture.loadFromFile(MARIO);
   marioSprite->texture.setSmooth(true);
   marioSprite->sprite.setTexture(marioSprite->texture);
   marioSprite->sprite.setTextureRect(sf::IntRect(0, 96, 32, 32));

   marioCollider->width = 32;
   marioCollider->height = 32;

   marioCollider->body = marioRigidBody;
   marioRigidBody->collider = marioCollider;
   marioRigidBody->isStatic = false;
   marioRigidBody->isUsingGravity = true;
   marioRigidBody->xVel = 0, marioRigidBody->yVel = 0;
}

void Mario::moveRight()
{
   goRight = true, goLeft = false;
   marioRigidBody->isStatic = false;
   marioRigidBody->AddForce(25.f, 0.f);
   sf::IntRect rect = marioSprite->sprite.getTextureRect();
   if (marioRigidBody->xVel >= 1)
      rect.left = 130;
   mario->scaleX = 1.5;
}

void Mario::moveLeft()
{
   goLeft = true, goRight = false;
   marioRigidBody->AddForce(-25.f, 0.f);
   sf::IntRect rect = marioSprite->sprite.getTextureRect();
   if (marioRigidBody->xVel <= -1)
      rect.left = 130;
   mario->scaleX = -1.5;
}

void Mario::setRectForWalking(sf::IntRect &rect)
{
   int maxLeft = 0, picWidth = 0;
   maxLeft = 99, picWidth = 33;

   if (rect.left >= maxLeft)
      rect.left = picWidth;
   else
      rect.left += picWidth;
}

void Mario::handleMovement()
{
   float waitingTime = 0.04;
   sf::IntRect rect = marioSprite->sprite.getTextureRect();

   if (timer1.getElapsedTime().asSeconds() > waitingTime)
   {
      waitingTime += 0.04;
      if (timer2.getElapsedTime().asSeconds() > waitingTime)
      {
         if (goRight == goLeft)
         {
            marioRigidBody->xVel = 0;
         }
         else if (goRight)
         {
            moveRight();
            // marioRigidBody->xVel = 25;
            setRectForWalking(rect);
         }
         else if (goLeft)
         {
            moveLeft();
            // marioRigidBody->xVel = -25;
            setRectForWalking(rect);
         }

         timer2.restart();
      }
      marioSprite->sprite.move(marioRigidBody->xVel, marioRigidBody->yVel);
      // mario->xPos += marioRigidBody->xVel;
      // mario->yPos += marioRigidBody->yVel;
      timer1.restart();
   }
   marioSprite->sprite.setTextureRect(rect);
}
