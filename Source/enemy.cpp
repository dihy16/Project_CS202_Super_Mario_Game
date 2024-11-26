#include "../header/enemy.h"

void WalkBehavior::move()
{
   // Walk implementation
   std::cout << "Walking on the ground." << std::endl;
}

void JumpBehavior::move()
{
   // Jump implementation
   std::cout << "Jumping." << std::endl;
}

// Enemy base class methods
Enemy::Enemy(int x, int y)
{
   display = moving = true;
   speed[0] = 20, speed[1] = 0;
   maxRect = 2, currentRect = 0;
   isKilled = onGround = fading = false;
   enemySprite.setPosition(x, y);
}

void Enemy::animation()
{
   if (timer.getElapsedTime().asSeconds() > 0.2f)
   {
      enemyRect.left = currentRect * enemyRect.width;
      enemySprite.setTextureRect(enemyRect);
      if (moving)
         currentRect++;
      if (currentRect == maxRect)
         currentRect = 0;
      timer.restart();
   }
   movementBehavior->move();
}

void Enemy::changeDirection()
{
   // Implement changing direction logic
}

void Enemy::checkGround()
{
   // Implement ground check logic
}

void Enemy::checkKilled()
{
   // Implement check killed logic
}

void Enemy::setKilled()
{
   // Implement set killed logic
}

void Enemy::setFading()
{
   // Implement set fading logic
}

void Enemy::draw(RenderWindow &window)
{
   if (display)
   {
      animation();
      window.draw(enemySprite);
   }
}

// Goomba class methods
Goomba::Goomba(int x, int y) : Enemy(x, y)
{
   enemyRect = IntRect(0, 0, 32, 31);
   enemySprite.setTextureRect(enemyRect);
   enemySprite.setOrigin(enemyRect.width / 2, enemyRect.height);
   enemySprite.setScale(1.5, 1.5);
   movementBehavior = make_unique<WalkBehavior>();
}

void Goomba::animation()
{
   Enemy::animation();
   std::cout << "Goomba specific animation." << std::endl;
}

// Koopa class methods
Koopa::Koopa(int x, int y) : Enemy(x, y)
{
   enemyRect = IntRect(0, 34, 32, 46);
   enemySprite.setTextureRect(enemyRect);
   enemySprite.setOrigin(enemyRect.width / 2, enemyRect.height);
   enemySprite.setScale(1.5, 1.5);
   movementBehavior = make_unique<WalkBehavior>();
}

void Koopa::animation()
{
   Enemy::animation();
   std::cout << "Koopa specific animation." << std::endl;
}

// HammerBro class methods
HammerBro::HammerBro(int x, int y) : Enemy(x, y)
{
   enemyRect = IntRect(0, 70, 32, 46);
   enemySprite.setTextureRect(enemyRect);
   enemySprite.setOrigin(enemyRect.width / 2, enemyRect.height);
   enemySprite.setScale(1.5, 1.5);
   movementBehavior = make_unique<JumpBehavior>();
}

void HammerBro::animation()
{
   Enemy::animation();
   std::cout << "HammerBro specific animation." << std::endl;
}

// PiranhaPlant class methods
PiranhaPlant::PiranhaPlant(int x, int y) : Enemy(x, y)
{
   enemyRect = IntRect(0, 120, 32, 46);
   enemySprite.setTextureRect(enemyRect);
   enemySprite.setOrigin(enemyRect.width / 2, enemyRect.height);
   enemySprite.setScale(1.5, 1.5);
   movementBehavior = make_unique<WalkBehavior>();
}

void PiranhaPlant::animation()
{
   Enemy::animation();
   std::cout << "PiranhaPlant specific animation." << std::endl;
}

// Factory Method implementation
unique_ptr<Enemy> EnemyFactory::createEnemy(const string &type, int x, int y)
{
   if (type == "Goomba")
   {
      return make_unique<Goomba>(x, y);
   }
   else if (type == "Koopa")
   {
      return make_unique<Koopa>(x, y);
   }
   else if (type == "HammerBro")
   {
      return make_unique<HammerBro>(x, y);
   }
   else if (type == "PiranhaPlant")
   {
      return make_unique<PiranhaPlant>(x, y);
   }
   else
   {
      return nullptr;
   }
}