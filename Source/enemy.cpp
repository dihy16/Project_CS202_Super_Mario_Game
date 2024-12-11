#include "./enemy.h"

Enemy::Enemy(int x, int y) {}
void Enemy::move() {}

void Enemy::initialize(int x, int y, sf::IntRect &rect, std::string name)
{
   currentRect = 0;
   maxRect = 2;
   display = moving = true;
   Entity *enemy = new Entity;
   RenderManager::GetInstance().listEntity.push_back(enemy);
   enemy->scaleX = 1.0;
   enemy->scaleY = 1.0;
   enemy->xPos = x;
   enemy->yPos = y;
   enemy->name = name;
   sr = AddComponent<SpriteRenderer>(enemy);
   sr->layer = 3;
   sr->texture.loadFromFile(ENEMY);
   sr->texture.setSmooth(true);
   sr->sprite.setTexture(sr->texture);
   sr->sprite.setTextureRect(rect);
   bc = AddComponent<BoxCollider>(enemy);
   bc->width = rect.width;
   bc->height = rect.height;
   rb = AddComponent<RigidBody>(enemy);
   bc->body = rb;
   rb->collider = bc;
   rb->isStatic = false;
   rb->xVel = 0.1, rb->yVel = 0;
   rb->isUsingGravity = true;
   enemyRect = rect;
   bc->OnColliderLanded =  [this](BoxCollider*)
    {
        RenderManager::GetInstance().debugText += "landed";
        bc->SetActive(false);
        rb->SetActive(false);
        sr->SetActive(false);
    };
   bc->OnHorizontalCollision = [this](BoxCollider* collider)
   {
      if (collider->body->GetOwner()->name == "mario")
      {
        RenderManager::GetInstance().debugText += " hp - 1 ";

      }
      else {
        RenderManager::GetInstance().debugText += " hit by something not mario";

      }
   };
}

Goomba::Goomba(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(0, 0, 32, 31); // live goomba
   // sf::IntRect rect(64, 0, 32, 31); dead goomba

   initialize(x, y, rect, "goomba");
}

void Goomba::kickFromTop(Mario *mario)
{
   state = Cramped;
   sr->sprite.setTextureRect(sf::IntRect(64, 0, 32, 31));
   rb->isStatic = true;
}

void Goomba::kickFromBottom(Mario *mario) {}

void Goomba::touchSide(Mario *mario) {}

void Goomba::setState(State state)
{
   this->state = state;
   if (state == Dead)
   {
      rb->isStatic = true;
      sr->sprite.setTextureRect(sf::IntRect(64, 0, 32, 31));
      // add score to player
      // play mario sound
   }
}

void Goomba::move()
{
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
   if (moving)
      sr->sprite.move(rb->xVel, rb->yVel);

   // sr->GetOwner()->xPos += rb->xVel;
}

Koopa::Koopa(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(0, 34, 32, 46); // live koopa
   // sf::IntRect rect(64, 36, 32, 42); dead koopa

   initialize(x, y, rect, "koopa");
}

void Koopa::kickFromTop(Mario *mario)
{
   state = Dead;
   sr->sprite.setTextureRect(sf::IntRect(64, 36, 32, 42));
   rb->isStatic = true;
}

void Koopa::kickFromBottom(Mario *mario) {}

void Koopa::touchSide(Mario *mario) {}

void Koopa::move()
{
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
   if (moving)
      sr->sprite.move(rb->xVel, rb->yVel);

   // sr->GetOwner()->xPos += rb->xVel;
   // sr->GetOwner()->yPos += rb->yVel;
}

HammerBro::HammerBro(int x, int y) : Enemy(x, y)
{
   // sf::IntRect rect(96, 161, 32, 46);
   sf::IntRect rect(160, 160, 32, 48);
   initialize(x, y, rect, "hammerBro");
}

void HammerBro::kickFromTop(Mario *mario) {}
void HammerBro::kickFromBottom(Mario *mario) {}
void HammerBro::touchSide(Mario *mario) {}

void HammerBro::move()
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

void HammerBro::throwHammer()
{
   hammer->getRigidBody()->AddForce(-1, -1);
   hammer->move();
}

Hammer::Hammer(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(96, 113, 32, 32);
   initialize(x, y, rect, "hammer");
   rb->isUsingGravity = false;
   gravityTimer.restart();
   sr->layer = 3;
}

void Hammer::kickFromTop(Mario *mario) {}
void Hammer::kickFromBottom(Mario *mario) {}
void Hammer::touchSide(Mario *mario) {}

void Hammer::move()
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

PiranhaPlant::PiranhaPlant(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(0, 80, 32, 46);
   initialize(x, y, rect, "piranhaPlant");
}

void PiranhaPlant::kickFromTop(Mario *mario)
{
   // mario receive damage
}

void PiranhaPlant::kickFromBottom(Mario *mario) {}

void PiranhaPlant::touchSide(Mario *mario)
{
   // mario receive damage
}

void PiranhaPlant::move()
{
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
   if (moving)
      sr->sprite.move(rb->xVel, rb->yVel);

   // sr->GetOwner()->xPos += rb->xVel;
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
   else if (type == "PiranhaPlant")
      return std::make_unique<PiranhaPlant>(x, y);
   else
      return nullptr;
}