#include "level.h"
#include <iostream>
using namespace std;

Level::Level(int level, bool resuming)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 2);
    int target;
    if (resuming)
    {
        mario->restoreState(GameStateMemento::loadState("Log/game_state.txt"));
    }
    else
    {
        mario = new Mario(8 * BLOCK_WIDTH, 12 * BLOCK_HEIGHT);
    }
    m = new Map(resuming);
    m->loadmap(level, 8 * BLOCK_WIDTH, 12 * BLOCK_HEIGHT);
    sf::Color c;
    std::string whichlevel;
    switch (level)
    {
    case 1:
        whichlevel = "Data/Level1";
        break;
    case 2:
        whichlevel = "Data/Level2";
        break;
    case 3:
        whichlevel = "Data/Level3";
        break;
    }
    sf::Image itemlayout;
    itemlayout.loadFromFile(whichlevel + "/layout.png");
    for (int i = 0; i < entitylayout.getSize().y; i++)
    {
        for (int j = 0; j < entitylayout.getSize().x; j++)
        {
            c = sf::Color(entitylayout.getPixel(j, i));
            if (c == sf::Color(255, 242, 0))
            {
                target = dist1(rng);
                switch (target)
                {
                case 0:
                    items.push_back(ItemFactory::createItem("Coin", j * BLOCK_WIDTH + 20, i * BLOCK_WIDTH + 20));
                    break;
                case 1:
                    items.push_back(ItemFactory::createItem("Mushroom", j * BLOCK_WIDTH + 20, i * BLOCK_WIDTH + 20));
                    break;
                case 2:
                    items.push_back(ItemFactory::createItem("Flower", j * BLOCK_WIDTH + 20, i * BLOCK_WIDTH + 20));
                    break;
                }
            }
        }
    }
    entitylayout.loadFromFile(whichlevel + "/entity.png");
    for (int i = 0; i < entitylayout.getSize().y; i++)
    {
        for (int j = 0; j < entitylayout.getSize().x; j++)
        {
            c = sf::Color(entitylayout.getPixel(j, i));
            if (c == sf::Color(95, 205, 228))
                ; // nothing
            else if (c == sf::Color(143, 86, 59))
                enemies.push_back(EnemyFactory::createEnemy("Goomba", j * BLOCK_WIDTH, i * BLOCK_HEIGHT));
            else if (c == sf::Color(153, 229, 80))
                enemies.push_back(EnemyFactory::createEnemy("Koopa", j * BLOCK_WIDTH, i * BLOCK_HEIGHT));
            else if (c == sf::Color(106, 190, 48))
                enemies.push_back(EnemyFactory::createEnemy("HammerBro", j * BLOCK_WIDTH, i * BLOCK_HEIGHT));
            else if (c == sf::Color(255, 255, 0))
                enemies.push_back(EnemyFactory::createEnemy("PiranhaPlant", j * BLOCK_WIDTH, i * BLOCK_HEIGHT));
        }
    }
    // enemies.push_back(EnemyFactory::createEnemy("Goomba", 300, 0));
    // enemies.push_back(EnemyFactory::createEnemy("Koopa", 400, 0));
    // enemies.push_back(EnemyFactory::createEnemy("PiranhaPlant", 500, 0));
    // enemies.push_back(EnemyFactory::createEnemy("HammerBro", 400, 700));
    // items.push_back(ItemFactory::createItem("Mushroom", 200, 700));
    // items.push_back(ItemFactory::createItem("Coin", 500, 700));
    // items.push_back(ItemFactory::createItem("Coin", 600, 700));
    // items.push_back(ItemFactory::createItem("Coin", 700, 700));
    // enemies.push_back(EnemyFactory::createEnemy("Goomba", 200, 0));
    // items.push_back(ItemFactory::createItem("Flower", 350, 700));
}
Level::~Level()
{
    delete mario;
    delete m;
};
void Level::start()
{
    display = true;
}
void Level::end()
{
    display = false;
}

void Level::handleKeyPress()
{
    mario->goLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    mario->goRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    mario->firing = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
    mario->marioRigidBody->isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}

void Level::execute()
{
    if (MarioGameManager::getInstance()->getState() == MarioGameManager::GameState::pause)
        return;
    handleKeyPress();
    mario->update(items);
    for (auto &enemy : enemies)
    {
        enemy->animation();
        enemy->collideWithMario(*mario);
        enemy->fadingAnimation();
    }

    for (auto &item : items)
    {
        item->animation();
        item->fadeOut();
    }
}

void Level::drawLevel()
{
    m->draw(RenderManager::GetInstance().window);
}

GameStateMemento Level::saveMarioState()
{
    return mario->saveState();
}
