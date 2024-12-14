#include "mario.h"

Mario::Mario(int x, int y)
{
   RenderManager::GetInstance().listEntity.push_back(mario);
   goRight = goLeft = goUp = false;

   mario->scaleX = 1.5;
   mario->scaleY = 1.5;
   mario->xPos = x;
   mario->yPos = y;
   mario->name = "mario";

   marioSprite->layer = 1;
   marioSprite->texture.loadFromFile(MARIO);
   marioSprite->texture.setSmooth(true);
   marioSprite->sprite.setTexture(marioSprite->texture);
   marioSprite->sprite.setTextureRect(sf::IntRect(0, 96, 32, 32));

   marioCollider->width = 48;
   marioCollider->height = 48;

   marioCollider->body = marioRigidBody;
   marioRigidBody->collider = marioCollider;
   marioRigidBody->isStatic = false;
   marioRigidBody->isUsingGravity = true;
   marioRigidBody->xVel = 0, marioRigidBody->yVel = 0;
   stateManager.setState(std::make_unique<SmallMario>());
}

void Mario::moveRight()
{
   goRight = true, goLeft = false;
   marioRigidBody->isStatic = false;
   marioRigidBody->AddForce(50.0f, 0.f);
   sf::IntRect rect = marioSprite->sprite.getTextureRect();
   // if (marioRigidBody->xVel >= 1)
   //    rect.left = 130;
   mario->scaleX = 1.5;
}

void Mario::moveLeft()
{
   goLeft = true, goRight = false;
   marioRigidBody->AddForce(-50.0f, 0.f);
   sf::IntRect rect = marioSprite->sprite.getTextureRect();
   // if (marioRigidBody->xVel <= -1)
   //    rect.left = 130;
   mario->scaleX = -1.5;
   // marioCollider->width = -48;
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
   float waitingTime = 0.05;
   sf::IntRect rect = marioSprite->sprite.getTextureRect();

   if (timer1.getElapsedTime().asSeconds() > waitingTime)
   {
      if (marioRigidBody->isJumping)
         rect.left = 161;
      waitingTime += 0.07;
      if (timer2.getElapsedTime().asSeconds() > waitingTime)
      {
         if (goRight == goLeft)
         {
            marioRigidBody->xVel = 0;
         }
         else if (goRight)
         {
            moveRight();
            setRectForWalking(rect);
         }
         else if (goLeft)
         {
            moveLeft();
            setRectForWalking(rect);
         }

         timer2.restart();
      }
      timer1.restart();
   }
   marioSprite->sprite.setTextureRect(rect);
}

// void Mario::handleCollision(std::vector<std::unique_ptr<Enemy>> &enemies)
// {
//    marioCollider->OnCollisionEnter = [&enemies](BoxCollider *bc)
//    {
//       // if (bc->GetOwner()->name == "goomba")
//       RenderManager::GetInstance().debugText += "hit";
//       for (auto &enemy : enemies)
//       {
//       }
//    };
// }

void Mario::handlePowerUp()
{
   stateManager.handlePowerUp();
}

void Mario::handleDamage()
{
   stateManager.handleDamage();
}