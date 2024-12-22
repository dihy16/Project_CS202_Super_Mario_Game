#include "./enemy.h"
#include <iostream>
Enemy::Enemy(int x, int y) {}
void Enemy::animation() {}

void Enemy::initialize(int x, int y, sf::IntRect &rect, std::string name)
{
   currentRect = 0;
   maxRect = 2;
   isKilled = false;

   RenderManager::GetInstance().listEntity.push_back(enemy);
   enemy->scaleX = 1.05;
   enemy->scaleY = 1.05;
   enemy->xPos = x;
   enemy->yPos = y;
   originX = x;
   originY = y;
   enemy->name = "enemy";
   enemy->tag = name;

   sr->layer = 3;
   sr->texture.loadFromFile(ENEMY);
   sr->texture.setSmooth(true);
   sr->sprite.setTexture(sr->texture);
   sr->sprite.setTextureRect(rect);

   bc->width = rect.width;
   bc->height = rect.height;

   bc->body = rb;
   rb->collider = bc;
   rb->isStatic = false;
   rb->isUsingGravity = true;
   rb->xVel = 0, rb->yVel = 0;
   enemyRect = rect;
   moveStrategy = std::make_unique<EnemyMoveStrategy>(*this);
}

Goomba::Goomba(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(0, 0, 32, 31); // live goomba
   initialize(x, y, rect, "goomba");
}

void Goomba::collideWithMario(Character &mario)
{
   bc->OnColliderLanded = [this](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "character")
      {
         RenderManager::GetInstance().debugText += "landed";
         bc->SetActive(false);
         // rb->SetActive(false);
         sr->sprite.setTextureRect(sf::IntRect(64, 0, 32, 31));
         isKilled = true;
         logEvent("Goomba killed", originX, originY);
      }
   };

   bc->OnHorizontalCollision = [this, &mario](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "character")
      {
         RenderManager::GetInstance().debugText += " hp - 1 ";
         mario.touchEnemy = true;
         MarioGameManager::getInstance()->playSound(MarioGameManager::mario_die);
      }
   };

   bc->OnCollisionEnter = [this](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "fireball")
      {
         RenderManager::GetInstance().debugText += " cut ";
         bc->SetActive(false);
         rb->SetActive(false);
         isKilled = true;
         logEvent("Goomba killed", originX, originY);
      }
   };
}

void Goomba::moveWithMario(Character &mario)
{
   float marioPos = mario.characterRigidBody->GetOwner()->xPos;
   float enemyPos = rb->GetOwner()->xPos;

   if (abs(marioPos - enemyPos) <= 500 && movetimer.getElapsedTime().asSeconds() > 1)
   {
      if ((enemyPos - marioPos) > 0)
         moveStrategy->move(-20, 0);
      else if ((marioPos - enemyPos) > 0)
         moveStrategy->move(20, 0);

      movetimer.restart();
   }
}

void Goomba::animation()
{
   moving = true;
   if (isKilled)
      return;
   if (timer.getElapsedTime().asSeconds() > 0.2)
   {
      enemyRect.left = currentRect * sr->sprite.getTextureRect().width;
      sr->sprite.setTextureRect(enemyRect);

      if (moving)
      {
         currentRect++;
         if (currentRect == maxRect)
            currentRect = 0;
      }

      timer.restart();
   }
}

void Goomba::fadingAnimation()
{
   if (!isKilled)
      return;
   if (timer.getElapsedTime().asSeconds() > 3)
      sr->SetActive(false);
}

Koopa::Koopa(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(224, 32, 32, 48); // live koopa
   initialize(x, y, rect, "koopa");
}

void Koopa::collideWithMario(Character &mario)
{
   bc->OnColliderLanded = [this](BoxCollider *)
   {
      RenderManager::GetInstance().debugText += "landed";
      if (state == Jumping)
      {
         sr->sprite.setTextureRect(sf::IntRect(0, 32, 32, 48));
         stateTimer.restart();
         state = Normal;
      }
      else if (state == Normal && stateTimer.getElapsedTime().asSeconds() > 1.5)
      {
         bc->SetActive(false);
         // rb->SetActive(false);

         sr->sprite.setTextureRect(sf::IntRect(64, 32, 32, 48));
         state = Hidden;
         isKilled = true;
         logEvent("Koopa killed", originX, originY);
      }
   };

   bc->OnHorizontalCollision = [this, &mario](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "character")
      {
         RenderManager::GetInstance().debugText += " hp - 1 ";
         mario.touchEnemy = true;
         MarioGameManager::getInstance()->playSound(MarioGameManager::mario_die);
      }
   };

   bc->OnCollisionEnter = [this](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "fireball")
      {
         RenderManager::GetInstance().debugText += " cut ";
         bc->SetActive(false);
         rb->SetActive(false);
         isKilled = true;
         logEvent("Koopa killed", originX, originY);
      }
   };
}

void Koopa::moveWithMario(Character &mario)
{
   float marioPos = mario.characterRigidBody->GetOwner()->xPos;
   float enemyPos = rb->GetOwner()->xPos;

   if (abs(marioPos - enemyPos) <= 500 && movetimer.getElapsedTime().asSeconds() > 1)
   {
      if ((enemyPos - marioPos) > 0)
      {
         moveStrategy->move(-40, 0);
         direction = Right;
      }
      else if ((marioPos - enemyPos) > 0)
      {
         moveStrategy->move(40, 0);
         direction = Left;
      }
      if (state == Jumping)
         rb->isJumping = true;

      movetimer.restart();
   }
}

void Koopa::animation()
{
   moving = true;
   if (isKilled)
      return;
   if (timer.getElapsedTime().asSeconds() > 0.2)
   {
      if (state == Jumping)
      {
         if (direction == Right)
            enemyRect.left = 224 + currentRect * sr->sprite.getTextureRect().width;
         else
            enemyRect.left = 736 + currentRect * sr->sprite.getTextureRect().width;
      }
      else if (state == Normal)
      {
         if (direction == Right)
            enemyRect.left = currentRect * sr->sprite.getTextureRect().width;
         else
            enemyRect.left = 960 + currentRect * sr->sprite.getTextureRect().width;
      }

      sr->sprite.setTextureRect(enemyRect);

      if (moving)
      {
         currentRect++;
         if (currentRect == maxRect)
            currentRect = 0;
      }

      timer.restart();
   }
}

void Koopa::fadingAnimation()
{
   if (!isKilled)
      return;
   if (timer.getElapsedTime().asSeconds() > 3)
      sr->SetActive(false);
}

HammerBro::HammerBro(int x, int y) : Enemy(x, y)
{
   // sf::IntRect rect(96, 161, 32, 46);
   sf::IntRect rect(160, 160, 32, 48);
   initialize(x, y, rect, "hammerBro");
}

void HammerBro::collideWithMario(Character &mario) {}

void HammerBro::moveWithMario(Character &mario) {}

void HammerBro::animation()
{
   maxRect = 4;
   if (timer.getElapsedTime().asSeconds() > 0.2)
   {
      enemyRect.left = 96 + currentRect * sr->sprite.getTextureRect().width;
      sr->sprite.setTextureRect(enemyRect);
      if (moving)
      {
         currentRect++;
         if (currentRect == maxRect)
            currentRect = 0;
      }
      if (throwTimer.getElapsedTime().asSeconds() > 3)
      {
         hammer = EnemyFactory::createEnemy("Hammer", sr->GetOwner()->xPos - 35, sr->GetOwner()->yPos - 30);
         throwTimer.restart();
      }
      if (hammer)
         throwHammer();
      timer.restart();
   }
   if (moving)
      sr->sprite.move(rb->xVel, rb->yVel);

   // sr->GetOwner()->xPos += rb->xVel;
}

void HammerBro::fadingAnimation() {}

void HammerBro::throwHammer()
{
   hammer->getRigidBody()->AddForce(-1, -1);
   hammer->animation();
}

Hammer::Hammer(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(96, 113, 32, 32);
   initialize(x, y, rect, "hammer");
   rb->isUsingGravity = false;
   gravityTimer.restart();
   sr->layer = 3;
}

void Hammer::collideWithMario(Character &mario) {}

void Hammer::moveWithMario(Character &mario) {}

void Hammer::animation()
{
   maxRect = 4;
   if (timer.getElapsedTime().asSeconds() > 0.2)
   {
      enemyRect.left = 96 + currentRect * sr->sprite.getTextureRect().width;
      sr->sprite.setTextureRect(enemyRect);

      if (moving)
      {
         currentRect++;
         if (currentRect == maxRect)
            currentRect = 0;
      }
      if (gravityTimer.getElapsedTime().asSeconds() > 1)
      {
         rb->AddForce(0, 4);
      }
      timer.restart();
   }

   if (moving)
      sr->sprite.move(rb->xVel, rb->yVel);

   sr->GetOwner()->xPos += rb->xVel;
   sr->GetOwner()->yPos += rb->yVel;
}

void Hammer::fadingAnimation() {}

PiranhaPlant::PiranhaPlant(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(0, 80, 32, 46);
   initialize(x, y, rect, "piranhaPlant");
   rb->isUsingGravity = false;
}

void PiranhaPlant::collideWithMario(Character &mario)
{
   bc->OnColliderLanded = [this, &mario](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "character")
      {
         RenderManager::GetInstance().debugText += " hp - 1 ";
         mario.touchEnemy = true;
         MarioGameManager::getInstance()->playSound(MarioGameManager::mario_die);
      }
   };

   bc->OnHorizontalCollision = [this, &mario](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "character")
      {
         RenderManager::GetInstance().debugText += " hp - 1 ";
         mario.touchEnemy = true;
         MarioGameManager::getInstance()->playSound(MarioGameManager::mario_die);
      }
   };

   bc->OnCollisionEnter = [this](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "fireball")
      {
         RenderManager::GetInstance().debugText += " cut ";
         bc->SetActive(false);
         // rb->SetActive(false);
         isKilled = true;
         logEvent("PiranhaPlant killed", originX, originY);
      }
   };
}

void PiranhaPlant::moveWithMario(Character &mario)
{
   float maxPos = 12 * BLOCK_HEIGHT - 46; // Bottom position
   float minPos = 11 * BLOCK_HEIGHT;      // Top position

   if (movetimer.getElapsedTime().asSeconds() > 1)
   {
      switch (state)
      {
      case MovingUp:
         if (rb->GetOwner()->yPos <= minPos)
         {
            rb->GetOwner()->yPos = minPos; // Ensure it stays at minPos
            state = WaitingAtTop;
            waitTimer.restart();
         }
         else
            rb->AddForce(0, -10);
         break;

      case WaitingAtTop:
         if (waitTimer.getElapsedTime().asSeconds() > 5)
            state = MovingDown;
         break;

      case MovingDown:
         if (rb->GetOwner()->yPos >= maxPos)
         {
            rb->GetOwner()->yPos = maxPos; // Ensure it stays at maxPos
            state = MovingUp;
         }
         else
            rb->AddForce(0, 10);
         break;
      }

      movetimer.restart();
   }
}

void PiranhaPlant::animation()
{
   moving = true;
   if (timer.getElapsedTime().asSeconds() > 0.2)
   {
      enemyRect.left = currentRect * sr->sprite.getTextureRect().width;
      sr->sprite.setTextureRect(enemyRect);

      if (moving)
      {
         currentRect++;
         if (currentRect == maxRect)
            currentRect = 0;
      }

      timer.restart();
   }
}

void PiranhaPlant::fadingAnimation()
{
   if (!isKilled)
      return;
   if (timer.getElapsedTime().asSeconds() > 3)
      sr->SetActive(false);
}

Gooner::Gooner(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(64, 113, 32, 32);
   initialize(x, y, rect, "gooner");
   rb->isUsingGravity = false;
   waitTimer.restart();
}

void Gooner::animation()
{
   maxRect = 3;
   if (timer.getElapsedTime().asSeconds() > 0.2)
   {
      enemyRect.top = 113 + currentRect * sr->sprite.getTextureRect().height;
      sr->sprite.setTextureRect(enemyRect);

      if (moving)
      {
         currentRect++;
         if (currentRect == maxRect)
            currentRect = 0;
      }

      timer.restart();
   }
}

void Gooner::collideWithMario(Character &mario)
{

   bc->OnCollisionEnter = [this, &mario](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "character")
      {
         RenderManager::GetInstance().debugText += " hp - 1 ";
         mario.touchEnemy = true;
         MarioGameManager::getInstance()->playSound(MarioGameManager::mario_die);
      }
      else
      {
         bc->SetActive(false);
         rb->SetActive(false);
         sr->SetActive(false);
      }
   };
}

void Gooner::moveWithMario(Character &mario)
{

   if (movetimer.getElapsedTime().asSeconds() > 0.5)
   {
      moveStrategy->move(-50, 0);
      movetimer.restart();
   }
}

void Gooner::fadingAnimation()
{
   if (waitTimer.getElapsedTime().asSeconds() > 10)
   {
      sr->SetActive(false);
      bc->SetActive(false);
      rb->SetActive(false);
   }
}

std::unique_ptr<Enemy> EnemyFactory::createEnemy(const std::string &type, int x, int y)
{
   if (type == "Goomba")
      return std::make_unique<Goomba>(x, y);
   else if (type == "Koopa")
      return std::make_unique<Koopa>(x, y);
   else if (type == "HammerBro")
      return std::make_unique<HammerBro>(x, y);
   else if (type == "Hammer")
      return std::make_unique<Hammer>(x, y);
   else if (type == "Gooner")
      return std::make_unique<Gooner>(x, y);
   else if (type == "PiranhaPlant")
      return std::make_unique<PiranhaPlant>(x, y);
   else
      return nullptr;
}

void EnemyFactory::deleteEnemyAtPosition(std::vector<std::unique_ptr<Enemy>> &enemies, int x, int y)
{
   auto it = std::remove_if(enemies.begin(), enemies.end(), [x, y](const std::unique_ptr<Enemy> &enemy)
                            { return static_cast<int>(enemy->getRigidBody()->GetOwner()->xPos) == x &&
                                     static_cast<int>(enemy->getRigidBody()->GetOwner()->yPos) == y; });
   enemies.erase(it, enemies.end());
}