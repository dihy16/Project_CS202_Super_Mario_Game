#include "level1.h"
Level1::Level1() : mario(100, 100), m("Data/maps.txt")
{
   m.blockgenerator(100, 12 * BLOCK_HEIGHT);
   // enemies.push_back(EnemyFactory::createEnemy("Goomba", 200, 700));
   // enemies.push_back(EnemyFactory::createEnemy("Koopa", 400, 700));
   // enemies.push_back(EnemyFactory::createEnemy("HammerBro", 400, 700));
   // enemies.push_back(EnemyFactory::createEnemy("PiranhaPlant", 500, 700));
   items.push_back(ItemFactory::createItem("Mushroom", 200, 700));
   items.push_back(ItemFactory::createItem("Coin", 500, 700));
   //   items.push_back(ItemFactory::createItem("Sparkle", 400, 100));
   items.push_back(ItemFactory::createItem("Flower", 350, 700));
};
void Level1::start()
{
   display = true;
}
void Level1::end()
{
   display = false;
}

void Level1::handleKeyPress()
{
   mario.goLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
   mario.goRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
   mario.marioRigidBody->isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}

void Level1::execute()
{
   handleKeyPress();
   mario.update();
   for (auto &enemy : enemies)
   {
      enemy->move();
      enemy->collideWithMario();
      enemy->fadingAnimation();
   }

   for (auto &item : items)
   {
      item->animation();
      item->fadeOut();
   }
}