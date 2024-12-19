#include "./items.h"

Item::Item(int x, int y) {}
void Item::animation() {}
void Item::fadeOut() {}

void Item::initialize(float x, float y, sf::IntRect &rect, std::string name, int maxRect)
{
   display = true;
   isTaken = false;
   fading = false;
   currentRect = 0;
   this->maxRect = maxRect;
   Entity *item = new Entity;
   RenderManager::GetInstance().listEntity.push_back(item);

   sr = AddComponent<SpriteRenderer>(item);
   bc = AddComponent<BoxCollider>(item);
   rb = AddComponent<RigidBody>(item);

   item->xPos = x;
   item->yPos = y;
   item->scaleX = 1.0;
   item->scaleY = 1.0;
   item->name = name;

   sr->layer = 3;
   if (item->name == "fireball")
   {
      sr->texture.loadFromFile(MARIO);
      item->scaleX = 1.4;
      item->scaleY = 1.4;
   }
   else
      sr->texture.loadFromFile(ITEM);
   sr->texture.setSmooth(true);
   sr->sprite.setTexture(sr->texture);
   sr->sprite.setTextureRect(rect);

   bc->width = rect.width * item->scaleX;
   bc->height = rect.height * item->scaleY;

   bc->body = rb;
   rb->collider = bc;
   rb->isStatic = false;
   rb->isUsingGravity = true;
   rb->xVel = 0, rb->yVel = 0;

   itemRect = rect;
}

Mushroom::Mushroom(int x, int y) : Item(x, y)
{
   sf::IntRect rect(128, 150, 32.5, 32);
   initialize(x, y, rect, "mushroom", 2);
}

void Mushroom::animation()
{
   if (timer.getElapsedTime().asSeconds() > 1.5)
   {
      itemRect.left = 128 + currentRect * sr->sprite.getTextureRect().width;
      if (fading)
         sr->sprite.setColor(sf::Color::Transparent);
      sr->sprite.setTextureRect(itemRect);
      currentRect++;
      if (currentRect == maxRect)
         currentRect = 0;

      timer.restart();
   }
}

void Mushroom::fadeOut()
{
   if (!rb->GetActive())
   {
      bc->SetActive(false);
      sr->SetActive(false);
   }
}

Coin::Coin(int x, int y) : Item(x, y)
{
   sf::IntRect rect(0, 86, 32, 32);
   initialize(x, y, rect, "coin", 4);
}

void Coin::animation()
{
   if (timer.getElapsedTime().asSeconds() > 0.2)
   {
      if (state == Sparkling)
      {
         maxRect = 6;
         itemRect.left = currentRect * sr->sprite.getTextureRect().width;
         // itemRect.top = 116;
         sr->sprite.setTextureRect(itemRect);
         currentRect++;
         if (currentRect == maxRect)
         {
            RenderManager::GetInstance().debugText += std::to_string(currentRect);
            currentRect = 0;
            finished = true;
         }
      }
      else if (state == Normal)
      {
         maxRect = 4;
         itemRect.left = currentRect * sr->sprite.getTextureRect().width;
         // itemRect.top = 86;
         sr->sprite.setTextureRect(itemRect);
         currentRect++;
         if (currentRect == maxRect)
            currentRect = 0;
      }
      timer.restart();
   }
}

void Coin::fadeOut()
{
   if (!rb->GetActive())
   {
      state = Sparkling;
      sr->sprite.setTextureRect(sf::IntRect(0, 116, 40, 32));
      itemRect = sf::IntRect(0, 116, 40, 32);
   }
   if (finished)
      sr->SetActive(false);
}

Flower::Flower(int x, int y) : Item(x, y)
{
   sf::IntRect rect(32, 213, 32, 30);
   initialize(x, y, rect, "flower", 3);
}

void Flower::animation()
{
   if (timer.getElapsedTime().asSeconds() > 0.2)
   {
      itemRect.left = 32 + currentRect * sr->sprite.getTextureRect().width;
      if (fading)
         sr->sprite.setColor(sf::Color::Transparent);
      sr->sprite.setTextureRect(itemRect);
      currentRect++;
      if (currentRect == maxRect)
         currentRect = 0;

      timer.restart();
   }
}

void Flower::fadeOut()
{
   if (!rb->GetActive())
   {
      bc->SetActive(false);
      sr->SetActive(false);
   }
}

Bullet::Bullet(int x, int y, bool direction) : Item(x, y)
{
   this->direction = direction; // true for right, false for left
   sf::IntRect rect(0, 0, 16, 16);
   initialize(x, y, rect, "fireball", 2);
   fadeTimer.restart();
}

void Bullet::animation()
{
   if (timer.getElapsedTime().asSeconds() > 0.2)
   {
      if (state == Flying)
      {
         if (!direction)
         {
            itemRect.left = 992 + currentRect * sr->sprite.getTextureRect().width;
            sr->sprite.setTextureRect(itemRect);
            currentRect++;
            if (currentRect == maxRect)
               currentRect = 0;

            rb->xVel = -120;
         }
         else
         {
            itemRect.left = currentRect * sr->sprite.getTextureRect().width;
            sr->sprite.setTextureRect(itemRect);
            currentRect++;
            if (currentRect == maxRect)
               currentRect = 0;

            rb->xVel = 120;
         }
         if (jumpTimer.getElapsedTime().asSeconds() > 0.2)
         {
            rb->isJumping = true;
            jumpTimer.restart();
         }
      }
      else if (state == Splash)
      {
         maxRect = 3;
         if (!direction)
         {
            itemRect.left = 960 - currentRect * sr->sprite.getTextureRect().width;
            sr->sprite.setTextureRect(itemRect);
            currentRect++;
            if (currentRect == maxRect)
            {
               currentRect = 0;
               finished = true;
            }
         }
         else
         {
            itemRect.left = 32 + currentRect * sr->sprite.getTextureRect().width;
            sr->sprite.setTextureRect(itemRect);
            currentRect++;
            if (currentRect == maxRect)
            {
               currentRect = 0;
               finished = true;
            }
         }
      }
      timer.restart();
   }
}

void Bullet::fadeOut()
{
   bc->OnCollisionEnter = [this](BoxCollider *collider)
   {
      if ((collider->body->GetOwner()->name == "enemy") || (collider->body->GetOwner()->name == "fireball"))
      {
         state = Splash;
         sr->sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
         bc->SetActive(false);
         rb->SetActive(false);
      }
   };
   if (finished)
      sr->SetActive(false);
   if (fadeTimer.getElapsedTime().asSeconds() > 3)
   {
      sr->SetActive(false);
      bc->SetActive(false);
      rb->SetActive(false);
   }
}

void Bullet::reset(int x, int y, bool direction)
{
   this->direction = direction;
   itemRect = sf::IntRect(0, 0, 16, 16);
   initialize(x, y, itemRect, "fireball", 2);
   state = Flying;
   finished = false;
   thrown = false;
   fadeTimer.restart();
   setActive(true);
}

BulletPool::BulletPool(int size)
{
   for (int i = 0; i < size; i++)
   {
      bullets.push_back(std::make_unique<Bullet>(0, 0, true));
   }
}

Bullet *BulletPool::acquireBullet(int x, int y, bool direction)
{
   for (auto &bullet : bullets)
   {
      if (!bullet->isActive())
      {
         bullet->reset(x, y, direction);
         return bullet.get();
      }
   }
   bullets.push_back(std::make_unique<Bullet>(x, y, direction));
   return bullets.back().get();
}

void BulletPool::releaseBullet(Bullet *bullet) { bullet->setActive(false); }

BulletPool ItemFactory::bulletPool(5);

std::unique_ptr<Item> ItemFactory::createItem(const std::string &type, int x, int y, bool direction)
{
   if (type == "Mushroom")
      return std::make_unique<Mushroom>(x, y);
   else if (type == "Coin")
      return std::make_unique<Coin>(x, y);
   else if (type == "Flower")
      return std::make_unique<Flower>(x, y);
   // else if (type == "Star")
   //    return std::make_unique<Star>(x, y);
   else if (type == "Fireball")
      // return std::unique_ptr<Item>(bulletPool.acquireBullet(x, y, direction));
      return std::make_unique<Bullet>(x, y, direction);
   return nullptr;
}
