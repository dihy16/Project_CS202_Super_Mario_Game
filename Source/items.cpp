#include "./items.h"

Item::Item(int x, int y) {}
void Item::animation() {}
void Item::fadeOut() {}

void Item::initialize(int x, int y, sf::IntRect &rect, std::string name, int maxRect)
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

   sr->layer = 3;
   sr->texture.loadFromFile(ITEM);
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

   item->xPos = x;
   item->yPos = y;
   item->name = name;

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
   sf::IntRect rect(0, 84, 32, 32);
   initialize(x, y, rect, "coin", 4);
}

void Coin::animation()
{
   if (timer.getElapsedTime().asSeconds() > 0.2)
   {
      if (state == Sparkling)
      {
         maxRect = 5;
         itemRect.left = currentRect * sr->sprite.getTextureRect().width;
         itemRect.top = 116;
         sr->sprite.setTextureRect(itemRect);
         currentRect++;
         if (currentRect == maxRect)
         {
            currentRect = 0;
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
   bc->OnCollisionEnter = [this](BoxCollider *collider)
   {
      if (collider->body->GetOwner()->name == "mario")
      {
         state = Sparkling;
         sr->sprite.setTextureRect(sf::IntRect(0, 116, 40, 32));
         bc->SetActive(false);
         rb->SetActive(false);
      }
   };
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

std::unique_ptr<Item> ItemFactory::createItem(const std::string &type, int x, int y)
{
   if (type == "Mushroom")
      return std::make_unique<Mushroom>(x, y);
   else if (type == "Coin")
      return std::make_unique<Coin>(x, y);
   else if (type == "Flower")
      return std::make_unique<Flower>(x, y);
   return nullptr;
}