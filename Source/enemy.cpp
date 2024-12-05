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
   rb->xVel = 0.001, rb->yVel = 0;

   enemyRect = rect;
}

Goomba::Goomba(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(0, 0, 32, 31); // live goomba
   // sf::IntRect rect(64, 0, 32, 31); dead goomba

   initialize(x, y, rect, "goomba");
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

   sr->GetOwner()->xPos += rb->xVel;
   sr->GetOwner()->yPos += rb->yVel;
}

Koopa::Koopa(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(0, 34, 32, 46); // live koopa
   // sf::IntRect rect(64, 36, 32, 42); dead koopa

   initialize(x, y, rect, "koopa");
}

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

   sr->GetOwner()->xPos += rb->xVel;
   sr->GetOwner()->yPos += rb->yVel;
}

HammerBro::HammerBro(int x, int y) : Enemy(x, y)
{
   // sf::IntRect rect(96, 161, 32, 46);
   sf::IntRect rect(160, 160, 32, 48);
   initialize(x, y, rect, "hammerBro");
}

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
      if (!hammer && throwTimer.getElapsedTime().asSeconds() > 2)
      {
         hammer = EnemyFactory::createEnemy("Hammer", sr->GetOwner()->xPos - 35, sr->GetOwner()->yPos - 30);
         throwTimer.restart();
      }
      else if (hammer)
         throwHammer();
      timer.restart();
   }
   if (moving)
      sr->sprite.move(rb->xVel, rb->yVel);

   sr->GetOwner()->xPos += rb->xVel;
   sr->GetOwner()->yPos += rb->yVel;
}

void HammerBro::throwHammer()
{
   hammer->getRigidBody()->AddForce(-1, -2);
   hammer->move();
}

Hammer::Hammer(int x, int y) : Enemy(x, y)
{
   sf::IntRect rect(96, 113, 32, 32);
   initialize(x, y, rect, "hammer");
   sr->layer = 1;
}

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
      // if (gravityTimer.getElapsedTime().asSeconds() > 2)
      // {
      //    rb->isUsingGravity = true;
      //    gravityTimer.restart();
      // }
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

   sr->GetOwner()->xPos += rb->xVel;
   sr->GetOwner()->yPos += rb->yVel;
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