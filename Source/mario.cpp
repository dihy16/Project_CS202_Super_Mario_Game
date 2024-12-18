#include "mario.h"

Mario::Mario(int x, int y)
{
   // RenderManager::GetInstance().listEntity.push_back(mario);
   goRight = goLeft = goUp = created = false;
   eatFlower = eatMushroom = touchEnemy = false;

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

bool Mario::getDirection()
{
   return direction == Right;
}

void Mario::moveRight()
{
   goRight = true, goLeft = false;
   direction = Right;
   marioRigidBody->isStatic = false;
   marioRigidBody->AddForce(50.0f, 0.f);
   sf::IntRect rect = marioSprite->sprite.getTextureRect();
   if (marioRigidBody->xVel <= -1)
   {
      // if (state == Small)
      //    rect.left = 132;
      // else if (state == Super || state == Fire)
      //    rect.left = 129;
   }
   else
      setRectForWalking(rect);
   if (!marioRigidBody->isJumping)
      marioSprite->sprite.setTextureRect(rect);
}

void Mario::moveLeft()
{
   goLeft = true, goRight = false;
   direction = Left;
   marioRigidBody->AddForce(-50.0f, 0.f);
   sf::IntRect rect = marioSprite->sprite.getTextureRect();
   if (marioRigidBody->xVel >= 1)
   {
      if (state == Small)
         rect.left = 1024 - 161;
      else if (state == Super || state == Fire)
         rect.left = 1024 - 164;
   }
   else
      setRectForWalking(rect);
   if (!marioRigidBody->isJumping)
      marioSprite->sprite.setTextureRect(rect);
}

void Mario::setRectForWalking(sf::IntRect &rect)
{
   int maxLeft = 0, picWidth = 0;
   if (direction == Right)
   {
      if (state == Small)
         maxLeft = 99, picWidth = 32;
      else if (state == Super || state == Fire)
         maxLeft = 96, picWidth = 30;

      if (rect.left >= maxLeft)
         rect.left = picWidth;
      else
         rect.left += picWidth;
   }
   else if (direction == Left)
   {
      if (state == Small)
         maxLeft = 1024 - 99, picWidth = 32;
      else if (state == Super || state == Fire)
         maxLeft = 1024 - 102, picWidth = 30;

      if (rect.left <= maxLeft)
         rect.left = 1024 - picWidth;
      else
         rect.left -= picWidth;
   }
}

void Mario::handleMovement()
{
   float waitingTime = 0.05;
   sf::IntRect rect = marioSprite->sprite.getTextureRect();

   if (timer1.getElapsedTime().asSeconds() > waitingTime)
   {
      if (marioRigidBody->isJumping)
      {
         if (direction == Right)
         {
            if (state == Small)
               rect.left = 162.5;
            else if (state == Super || state == Fire)
               rect.left = 161;
         }
         else if (direction == Left)
         {
            if (state == Small)
               rect.left = 1024 - 189.5;
            else if (state == Super || state == Fire)
               rect.left = 1024 - 191;
         }

         MarioGameManager::getInstance()->playSound(MarioGameManager::jump);
      }
      if (firing)
      {
         created = true;
         if (state == Super || state == Fire)
         {
            if (direction == Right)
               rect.left = 224;
            else
               rect.left = 1024 - 248;
         }
         MarioGameManager::getInstance()->playSound(MarioGameManager::fireball);
      }
      marioSprite->sprite.setTextureRect(rect);

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
   stand();
}

void Mario::stand()
{
   if (!goRight && !goLeft && !marioRigidBody->isJumping && !firing)
   {
      if (state == Small)
      {
         if (direction == Right)
            marioSprite->sprite.setTextureRect(sf::IntRect(0, 96, 28, 32));
         else if (direction == Left)
            marioSprite->sprite.setTextureRect(sf::IntRect(996, 96, 28, 32));
      }

      else if (state == Super || state == Fire)
      {
         if (direction == Right)
            marioSprite->sprite.setTextureRect(sf::IntRect(0, 36, 28, 60));
         else if (direction == Left)
            marioSprite->sprite.setTextureRect(sf::IntRect(1024 - 28, 36, 28, 60));
      }
   }
}

void Mario::animation1(float duration, float interval, std::function<void()> onComplete, bool &finished)
{
   static sf::Clock blinkTimer;
   float elapsed = blinkTimer.getElapsedTime().asMilliseconds();
   marioCollider->width = 48;
   marioCollider->height = 86;

   if (elapsed > duration)
   {
      marioSprite->sprite.setColor(sf::Color::White); // Reset to normal
      blinkTimer.restart();                           // Reset timer for next use
      finished = false;
      if (onComplete)
         onComplete(); // Call the completion callback
      return;
   }

   // Toggle visibility
   if (duration == 1000)
   {
      if (int(elapsed / interval) % 2 == 0)
         marioSprite->sprite.setTextureRect(sf::IntRect(0, 96, 28, 32));
      else
         marioSprite->sprite.setTextureRect(sf::IntRect(0, 36, 28, 60));
   }
   else if (duration == 1200)
   {
      if (int(elapsed / interval) % 2 == 0)
         marioSprite->texture.loadFromFile(MARIO);

      else
         marioSprite->texture.loadFromFile(SUPERMARIO);

      marioSprite->texture.setSmooth(true);
      marioSprite->sprite.setTexture(marioSprite->texture);
      marioSprite->sprite.setTextureRect(sf::IntRect(0, 36, 28, 60));
   }
}

void Mario::animation2(float duration, float interval, std::function<void()> onComplete, bool &finished, State &state)
{
   static sf::Clock blinkTimer;
   float elapsed = blinkTimer.getElapsedTime().asMilliseconds();
   marioCollider->width = 48;
   marioCollider->height = 48;

   if (elapsed > duration)
   {
      marioSprite->sprite.setColor(sf::Color::White); // Reset to normal
      blinkTimer.restart();                           // Reset timer for next use
      finished = false;
      if (onComplete)
         onComplete(); // Call the completion callback
      return;
   }

   if (state == Small)
   {
      if (int(elapsed / interval) % 2 == 0)
         marioSprite->sprite.setColor(sf::Color::Transparent);
      // RenderManager::GetInstance().debugText += "1 ";
      else
         marioSprite->sprite.setColor(sf::Color::White);
      // RenderManager::GetInstance().debugText += "2 ";
   }
   else if (state == Super || state == Fire)
   {
      if (int(elapsed / interval) % 2 == 0)
      {
         marioSprite->sprite.setTextureRect(sf::IntRect(0, 36, 28, 60));
         RenderManager::GetInstance().debugText += "1 ";
      }
      else
      {
         marioSprite->sprite.setTextureRect(sf::IntRect(0, 96, 28, 32));
         RenderManager::GetInstance().debugText += "2 ";
      }
   }
}

void Mario::handlePowerUp()
{
   marioCollider->OnCollisionEnter = [this](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "mushroom")
      {
         // Animate Mario and handle state transition
         eatMushroom = true;
         stateTimer.restart();
         collider->body->SetActive(false);
         MarioGameManager::getInstance()->playSound(MarioGameManager::powerup);
         logEvent("Mushroom collected", mario->xPos, mario->yPos);
         MarioGameManager::getInstance()->addScore(MarioGameManager::Mushroom);
      }
      else if (collider->body->GetOwner()->name == "coin")
      {
         MarioGameManager::getInstance()->addCoin();
         MarioGameManager::getInstance()->playSound(MarioGameManager::add_coin);
         collider->body->SetActive(false);
         MarioGameManager::getInstance()->addScore(MarioGameManager::Coin);
         logEvent("Coin collected", mario->xPos, mario->yPos);
      }
      else if (collider->body->GetOwner()->name == "flower")
      {
         eatFlower = true;
         stateTimer.restart();
         collider->body->SetActive(false);
         MarioGameManager::getInstance()->playSound(MarioGameManager::powerup);
         logEvent("Flower collected", mario->xPos, mario->yPos);
         MarioGameManager::getInstance()->addScore(MarioGameManager::Flower);
      }
   };
   if (eatMushroom)
   {
      animation1(1000, 100, [this]()
                 {
                   // Transition to Super Mario state
                   state = Super;
                   marioSprite->sprite.setTextureRect(sf::IntRect(0, 36, 28, 60)); }, eatMushroom);
   }
   if (eatFlower)
   {
      animation1(1200, 100, [this]()
                 {
                   // Transition to Fire Mario state
                   state = Fire;
                   marioSprite->texture.loadFromFile(SUPERMARIO);
                   marioSprite->texture.setSmooth(true);
                   marioSprite->sprite.setTexture(marioSprite->texture);
                   marioSprite->sprite.setTextureRect(sf::IntRect(0, 36, 28, 60)); }, eatFlower);
   }
}

void Mario::handleEnemy()
{
   if (touchEnemy)
   {
      if (state == Small)
      {
         animation2(1000, 50, [this]()
                    {
                       // loss a life
                    },
                    touchEnemy, state);
      }
      else if (state == Super || state == Fire)
      {
         animation2(1000, 50, [this]()
                    {
         state = Small;
         marioSprite->sprite.setTextureRect(sf::IntRect(0, 96, 28, 32)); }, touchEnemy, state);
      }
   }
}

void Mario::update(std::vector<std::unique_ptr<Item>> &items)
{
   handleMovement();
   handlePowerUp();
   handleEnemy();
   if (firing && created && timer3.getElapsedTime().asSeconds() > 1)
   {
      bool bulletDirection = (direction == Right);
      if (bulletDirection)
         items.push_back(ItemFactory::createItem("Fireball", mario->xPos + marioCollider->width + 1, mario->yPos, bulletDirection));
      else
         items.push_back(ItemFactory::createItem("Fireball", mario->xPos - 20, mario->yPos, bulletDirection));
      created = false;
      timer3.restart();
   }
   if (stateTimer.getElapsedTime().asSeconds() > 60)
   {
      if (state != Small)
      {
         state = Small;
         marioSprite->sprite.setTextureRect(sf::IntRect(0, 96, 28, 32));
         marioCollider->width = 48;
         marioCollider->height = 48;
      }
   }
}

GameStateMemento Mario::saveState()
{
   std::vector<Entity *> entities = RenderManager::GetInstance().listEntity;
   MarioState marioState;
   marioState.xPos = mario->xPos;
   marioState.yPos = mario->yPos;
   marioState.lives = MarioGameManager::getInstance()->getLives();
   marioState.coins = MarioGameManager::getInstance()->getCoins();
   marioState.score = MarioGameManager::getInstance()->getScore();
   marioState.time = MarioGameManager::getInstance()->getTimeRemaining();
   switch (state)
   {
   case Small:
      marioState.state = "Small";
      break;
   case Super:
      marioState.state = "Super";
      break;
   case Fire:
      marioState.state = "Fire";
      break;
   }
   return GameStateMemento(marioState, entities);
}

void Mario::restoreState(const GameStateMemento &memento)
{
   mario->xPos = memento.marioState.xPos;
   mario->yPos = memento.marioState.yPos;
   MarioGameManager::getInstance()->setLives(memento.marioState.lives);
   MarioGameManager::getInstance()->setCoins(memento.marioState.coins);
   MarioGameManager::getInstance()->setScore(memento.marioState.score);
   MarioGameManager::getInstance()->setTimeRemaining(memento.marioState.time);
   if (memento.marioState.state == "Small")
      state = Small;
   else if (memento.marioState.state == "Super")
      state = Super;
   else if (memento.marioState.state == "Fire")
      state = Fire;

   if (state == Fire)
   {
      marioSprite->texture.loadFromFile(SUPERMARIO);
      marioSprite->texture.setSmooth(true);
      marioSprite->sprite.setTexture(marioSprite->texture);
   }
   if (state == Super || state == Fire)
   {
      marioSprite->sprite.setTextureRect(sf::IntRect(0, 36, 28, 60));
      marioCollider->width = 48;
      marioCollider->height = 86;
   }
   RenderManager::GetInstance().listEntity = memento.entities;
}