#include "./items.h"

Item::Item(int x, int y) {}
void Item::animation() {}
void Item::fadeOut() {}

void Item::initialize(float x, float y, sf::IntRect &rect, std::string name, int maxRect)
{
   display = true;
   isTaken = false;
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

   sr->layer = 4;
   if (item->name == "fireball")
   {
      sr->texture.loadFromFile(MARIO);
      item->scaleX = 1.5;
      item->scaleY = 1.5;
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
   if (item->name == "fireball")
      sr->SetActive(true);
   else
      sr->SetActive(false);
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
   else if (isTouch)
   {
      bc->SetActive(true);
      sr->SetActive(true);
      rb->AddForce(-20, 0);
      isTouch = false;
      isMoving = true;
      dropTimer.restart();
   }
   if (isMoving && dropTimer.getElapsedTime().asSeconds() >= 3)
   {
      rb->xVel = 0;
      isMoving = false;
   }
}

Coin::Coin(int x, int y) : Item(x, y)
{
   sf::IntRect rect(0, 86, 32, 31);
   initialize(x, y, rect, "coin", 4);
}

void Coin::animation()
{
   if (timer.getElapsedTime().asSeconds() > 0.2)
   {
      if (state == Sparkling)
      {
         maxRect = 5;
         itemRect.left = tempRect * 40;
         itemRect.top = 116;
         itemRect.width = 40;
         itemRect.height = 32;
         sr->sprite.setTextureRect(itemRect);
         tempRect++;
         if (tempRect == maxRect)
         {
            tempRect = 0;
            finished = true;
         }
      }
      else if (state == Normal)
      {
         maxRect = 4;
         itemRect.left = currentRect * sr->sprite.getTextureRect().width;
         itemRect.top = 86;
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
   }
   else if (isTouch)
   {
      bc->SetActive(true);
      sr->SetActive(true);
      rb->AddForce(-20, 0);
      isTouch = false;
      isMoving = true;
      dropTimer.restart();
   }
   if (isMoving && dropTimer.getElapsedTime().asSeconds() >= 3)
   {
      rb->xVel = 0;
      isMoving = false;
   }
   if (finished)
   {
      sr->SetActive(false);
      bc->SetActive(false);
   }
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
   else if (isTouch)
   {
      bc->SetActive(true);
      sr->SetActive(true);
      rb->AddForce(-20, 0);
      isTouch = false;
      isMoving = true;
      dropTimer.restart();
   }

   if (isMoving && dropTimer.getElapsedTime().asSeconds() >= 3)
   {
      rb->xVel = 0;
      isMoving = false;
   }
}

Bullet::Bullet(int x, int y, bool direction) : Item(x, y)
{
   this->direction = direction; // true for right, false for left
   sf::IntRect rect(0, 0, 16, 16);
   initialize(x, y, rect, "fireball", 2);
   fadeTimer.restart();
   jumpTimer.restart();
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
      if ((collider->body->GetOwner()->name == "enemy"))
      {
         state = Splash;
         sr->sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
         bc->SetActive(false);
         rb->SetActive(false);
      }
   };
   if (fadeTimer.getElapsedTime().asSeconds() > 4 || finished)
   {
      sr->SetActive(false);
      bc->SetActive(false);
      rb->SetActive(false);
   }
}

std::unique_ptr<Item> ItemFactory::createItem(const std::string &type, int x, int y, bool direction)
{
   if (type == "Mushroom")
      return std::make_unique<Mushroom>(x, y);
   else if (type == "Coin")
      return std::make_unique<Coin>(x, y);
   else if (type == "Flower")
      return std::make_unique<Flower>(x, y);
   else if (type == "Fireball")
      return std::make_unique<Bullet>(x, y, direction);
   return nullptr;
}

void ItemFactory::deleteItemAtPosition(std::vector<std::unique_ptr<Item>> &items, int x, int y)
{
   auto it = std::remove_if(items.begin(), items.end(), [x, y](const std::unique_ptr<Item> &item)
                            { return static_cast<int>(item->getRigidBody()->GetOwner()->xPos) == x &&
                                     static_cast<int>(item->getRigidBody()->GetOwner()->yPos) == y; });
   items.erase(it, items.end());
}
