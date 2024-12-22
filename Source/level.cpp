#include "level.h"
#include <iostream>
using namespace std;

Level::Level(int level, bool resuming, bool isMario)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 2);
    int target;
    this->isMario = isMario;
    if (resuming)
    {
        if (isMario)
            mario->restoreState(GameStateMemento::loadState(MARIO_LOG));
        else
            luigi->restoreState(GameStateMemento::loadState(MARIO_LOG));
    }
    else
    {
        if (isMario)
            mario = new Mario(8 * BLOCK_WIDTH, 100);
        else
            luigi = new Luigi(8 * BLOCK_WIDTH, 100);
    }
    m = new Map(resuming);
    m->loadmap(level, 8 * BLOCK_WIDTH, 12 * BLOCK_HEIGHT);
    sf::Color c;
    std::string whichlevel;
    lv = level;
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
    for (int i = 0; i < itemlayout.getSize().y; i++)
    {
        for (int j = 0; j < itemlayout.getSize().x; j++)
        {
            c = sf::Color(itemlayout.getPixel(j, i));
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
            else if (c == sf::Color(153, 229, 80))
            {
                if (i == 0 || sf::Color(itemlayout.getPixel(j, i - 1)) != c)
                {
                    f = new Flag(j * BLOCK_WIDTH + 35, i * BLOCK_WIDTH + 67);
                    RenderManager::GetInstance().listEntity.push_back(f);
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
    enemies.push_back(EnemyFactory::createEnemy("Koopa", 900, 0));
    // enemies.push_back(EnemyFactory::createEnemy("PiranhaPlant", 500, 0));
    // enemies.push_back(EnemyFactory::createEnemy("Gooner", 1000, 700));
    // items.push_back(ItemFactory::createItem("Mushroom", 200, 700));
    // items.push_back(ItemFactory::createItem("Coin", 1000, 700));
    // items.push_back(ItemFactory::createItem("Coin", 1050, 700));
    // items.push_back(ItemFactory::createItem("Coin", 1100, 700));
    // items.push_back(ItemFactory::createItem("Flower", 1200, 700));

    timer.restart();
}
Level::~Level()
{
    if (isMario)
        delete mario;
    else
        delete luigi;
    delete m;
};

void Level::end()
{
    if (isMario)
    {
        if (mario->touchFlag)
        {
            f->rb->isUsingGravity = true;
            f->rb->isStatic = false;
            finished = true;
            if (mario->finishTimer.getElapsedTime().asSeconds() > 3)
            {
                MarioGameManager::getInstance()->setCurrentLevel(lv + 1);
                MarioGameManager::getInstance()->setState(MarioGameManager::GameState::status);
                DeleteObjects();
                MarioGameManager::getInstance()->loadLevel(false);
                mario->finishTimer.restart();
                MarioGameManager::getInstance()->updateHighScores(MarioGameManager::getInstance()->getScore(), MarioGameManager::getInstance()->getStringCurrentTime());
                saveHighScores(MarioGameManager::getInstance()->getVectorHiScore(), HIGHSCORE_FILE);

            }
        }
    }
    else
    {
        if (luigi->touchFlag)
        {
            f->rb->isUsingGravity = true;
            f->rb->isStatic = false;
            finished = true;
            if (luigi->finishTimer.getElapsedTime().asSeconds() > 3)
            {
                MarioGameManager::getInstance()->setCurrentLevel(lv + 1);
                MarioGameManager::getInstance()->setState(MarioGameManager::GameState::status);
                DeleteObjects();
                MarioGameManager::getInstance()->loadLevel(false);
                luigi->finishTimer.restart();
                MarioGameManager::getInstance()->updateHighScores(MarioGameManager::getInstance()->getScore(), MarioGameManager::getInstance()->getStringCurrentTime());
                saveHighScores(MarioGameManager::getInstance()->getVectorHiScore(), HIGHSCORE_FILE);

            }
        }
    }
    if (!finished)
        f->animation();
}

void Level::handleKeyPress()
{
    if (isMario)
    {
        mario->goLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        mario->goRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        mario->firing = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
        mario->characterRigidBody->isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    }
    else
    {
        luigi->goLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        luigi->goRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        luigi->firing = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
        luigi->characterRigidBody->isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    }
}

void Level::execute()
{
    if (MarioGameManager::getInstance()->getState() == MarioGameManager::GameState::pause)
        return;
    handleKeyPress();
    if (isMario)
        mario->update(items, 40);
    else
        luigi->update(items, 30);
    for (auto &enemy : enemies)
    {
        enemy->animation();
        if (isMario)
        {
            enemy->collideWithMario(*mario);
            enemy->moveWithMario(*mario);
        }
        else
        {
            enemy->collideWithMario(*luigi);
            enemy->moveWithMario(*luigi);
        }

        enemy->fadingAnimation();
    }

    for (auto &item : items)
    {
        item->animation();
        item->fadeOut();
    }
    end();
}

void Level::drawLevel()
{
    m->draw(RenderManager::GetInstance().window);
}

GameStateMemento Level::saveMarioState()
{
    if (isMario)
        return mario->saveState();
    return luigi->saveState();
}

void Flag::animation()
{
    if (timer.getElapsedTime().asSeconds() > 0.3)
    {
        flagRect.left = currentRect * sr->sprite.getTextureRect().width;
        sr->sprite.setTextureRect(flagRect);

        if (!finished)
            currentRect++;
        if (currentRect == maxRect)
            currentRect = 0;

        timer.restart();
    }
}