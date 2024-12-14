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

   marioSprite->layer = 2;
   marioSprite->texture.loadFromFile(MARIO);
   marioSprite->texture.setSmooth(true);
   marioSprite->sprite.setTexture(marioSprite->texture);
   marioSprite->sprite.setTextureRect(sf::IntRect(0, 96, 28, 32));

   marioCollider->width = 48;
   marioCollider->height = 48;

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
   marioRigidBody->AddForce(50.0f, 0.f);
   sf::IntRect rect = marioSprite->sprite.getTextureRect();
   if (marioRigidBody->xVel <= -1)
   {
      if (state == Small)
         rect.left = 132;
      else if (state == Super || state == Fire)
         rect.left = 129;
   }
   else
      setRectForWalking(rect);
   if (!marioRigidBody->isJumping)
      marioSprite->sprite.setTextureRect(rect);
   mario->scaleX = 1.5;
}

void Mario::moveLeft()
{
   goLeft = true, goRight = false;
   marioRigidBody->AddForce(-50.0f, 0.f);
   sf::IntRect rect = marioSprite->sprite.getTextureRect();
   if (marioRigidBody->xVel >= 1)
   {
      if (state == Small)
         rect.left = 132;
      else if (state == Super || state == Fire)
         rect.left = 129;
   }
   else
      setRectForWalking(rect);
   if (!marioRigidBody->isJumping)
      marioSprite->sprite.setTextureRect(rect);
   mario->scaleX = -1.5;
   // marioCollider->width = -48;
}

void Mario::setRectForWalking(sf::IntRect &rect)
{
   int maxLeft = 0, picWidth = 0;
   if (state == Small)
      maxLeft = 99, picWidth = 33;
   else if (state == Super || state == Fire)
      maxLeft = 96, picWidth = 32;

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
      {
         if (state == Small)
            rect.left = 162.5;
         else if (state == Super || state == Fire)
            rect.left = 161;
         marioSprite->sprite.setTextureRect(rect);
      }
      waitingTime += 0.07;
      if (timer2.getElapsedTime().asSeconds() > waitingTime)
      {
         if (goRight == goLeft)
            marioRigidBody->xVel = 0;
         else if (goRight)
            moveRight();
         else if (goLeft)
            moveLeft();

         timer2.restart();
      }
      timer1.restart();
   }
   // marioSprite->sprite.setTextureRect(rect);
   stand();
}

void Mario::stand()
{
   if (!goRight && !goLeft && !marioRigidBody->isJumping)
   {
      if (state == Small)
         marioSprite->sprite.setTextureRect(sf::IntRect(0, 96, 28, 32));
      else if (state == Super || state == Fire)
         marioSprite->sprite.setTextureRect(sf::IntRect(0, 36, 31, 60));
   }
}

void Mario::handlePowerUp()
{
   marioCollider->OnCollisionEnter = [this](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "mushroom")
      {
         state = Super;
         marioSprite->sprite.setTextureRect(sf::IntRect(0, 36, 31, 60));
         marioCollider->width = 48;
         marioCollider->height = 86;
         collider->body->SetActive(false);
      }
      else if (collider->body->GetOwner()->name == "coin")
      {
         // collider->body->SetActive(false);
         // increase coin state and score and play sound
      }
      else if (collider->body->GetOwner()->name == "flower")
      {
         state = Fire;
         // marioSprite->sprite.setTexture(superMarioTexture);
         marioSprite->texture.loadFromFile(SUPERMARIO);
         marioSprite->texture.setSmooth(true);
         marioSprite->sprite.setTexture(marioSprite->texture);
         marioSprite->sprite.setTextureRect(sf::IntRect(0, 36, 31, 60));

         marioCollider->width = 48;
         marioCollider->height = 86;
         collider->body->SetActive(false);
      }
   };
}

void Mario::update()
{
   handleMovement();
   handlePowerUp();
}