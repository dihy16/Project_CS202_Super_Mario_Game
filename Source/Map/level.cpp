#include "level.h"
#include <iostream>
using namespace std;

Level::Level(int level, bool resuming, bool isMarioSelected)
{
    isMario = isMarioSelected;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 2);
    if (resuming)
    {
        GameStateMemento oldState = GameStateMemento::loadState(MARIO_LOG);
        if (isMario)
        {
            mario = new Mario(oldState.marioState.xPos + 200, oldState.marioState.yPos);
            mario->restoreState(oldState);
        }
        else
        {
            luigi = new Luigi(oldState.marioState.xPos + 200, oldState.marioState.yPos);
            luigi->restoreState(oldState);
        }
    }
    else
    {
        if (isMario)
            mario = new Mario(8 * BLOCK_WIDTH, 100);
        else
            luigi = new Luigi(8 * BLOCK_WIDTH, 100);
        // clear txt file when starting new game
        clearLog();
    }
    m = new Map(resuming);
    m->loadmap(level, 8 * BLOCK_WIDTH, 12 * BLOCK_HEIGHT);
    sf::Color c;
    lv = level;
    loadItems(level, rng, dist1);
    loadEnemies(level);
    if (resuming)
        applyLog(MAP_LOG);
    // timer.restart();
}

void Level::loadItems(int level, std::mt19937 &rng, std::uniform_int_distribution<std::mt19937::result_type> &dist1)
{
    sf::Image itemlayout;
    itemlayout.loadFromFile("Data/Level" + std::to_string(level) + "/layout.png");
    int target;

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
                    items.push_back(ItemFactory::createItem("Coin", j * BLOCK_WIDTH + 20, i * BLOCK_WIDTH - 32));
                    break;
                case 1:
                    items.push_back(ItemFactory::createItem("Mushroom", j * BLOCK_WIDTH + 20, i * BLOCK_WIDTH - 32));
                    break;
                case 2:
                    items.push_back(ItemFactory::createItem("Flower", j * BLOCK_WIDTH + 20, i * BLOCK_WIDTH - 32));
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
}

void Level::loadEnemies(int level)
{
    sf::Image entitylayout;
    entitylayout.loadFromFile("Data/Level" + std::to_string(level) + "/entity.png");
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
            // else if (c == sf::Color(106, 190, 48))
            //     enemies.push_back(EnemyFactory::createEnemy("HammerBro", j * BLOCK_WIDTH, i * BLOCK_HEIGHT));
            else if (c == sf::Color(255, 255, 0))
                enemies.push_back(EnemyFactory::createEnemy("PiranhaPlant", j * BLOCK_WIDTH, i * BLOCK_HEIGHT));
        }
    }
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
            if (mario->finishTimer.getElapsedTime().asSeconds() > 1.5)
            {
                MarioGameManager::getInstance()->setCurrentLevel(lv + 1);
                DeleteObjects();
                MarioGameManager::getInstance()->loadLevel(false, true);
                MarioGameManager::getInstance()->setState(MarioGameManager::GameState::status);
                mario->finishTimer.restart();
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
            if (luigi->finishTimer.getElapsedTime().asSeconds() > 1.5)
            {
                MarioGameManager::getInstance()->setCurrentLevel(lv + 1);
                DeleteObjects();
                MarioGameManager::getInstance()->loadLevel(false, false);
                MarioGameManager::getInstance()->setState(MarioGameManager::GameState::status);
                luigi->finishTimer.restart();
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
    if (MarioGameManager::getInstance()->getState() != MarioGameManager::GameState::playing)
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
    else
        return luigi->saveState();
}

void Flag::animation()
{
    // if (timer.getElapsedTime().asSeconds() > 0.3)
    // {
    //     flagRect.left = currentRect * sr->sprite.getTextureRect().width;
    //     sr->sprite.setTextureRect(flagRect);

    //     if (!finished)
    //         currentRect++;
    //     if (currentRect == maxRect)
    //         currentRect = 0;

    //     timer.restart();
    // }
}

void Level::applyLog(const std::string &logFile)
{
    std::ifstream file(logFile);
    std::string line;
    while (std::getline(file, line))
    {
        int x, y;
        if (sscanf(line.c_str(), "Mushroom collected %d %d", &x, &y) == 2)
        {
            ItemFactory::deleteItemAtPosition(items, x, y);
        }
        else if (sscanf(line.c_str(), "Coin collected %d %d", &x, &y) == 2)
        {
            ItemFactory::deleteItemAtPosition(items, x, y);
        }
        else if (sscanf(line.c_str(), "Flower collected %d %d", &x, &y) == 2)
        {
            ItemFactory::deleteItemAtPosition(items, x, y);
        }
        else if (sscanf(line.c_str(), "Goomba killed %d %d", &x, &y) == 2)
        {
            EnemyFactory::deleteEnemyAtPosition(enemies, x, y);
        }
        else if (sscanf(line.c_str(), "Koopa killed %d %d", &x, &y) == 2)
        {
            EnemyFactory::deleteEnemyAtPosition(enemies, x, y);
        }
        else if (sscanf(line.c_str(), "PiranhaPlant killed %d %d", &x, &y) == 2)
        {
            EnemyFactory::deleteEnemyAtPosition(enemies, x, y);
        }
    }
}

void Level::clearLog()
{
    // Open game_log.txt in write mode to clear its contents
    std::ofstream logFile(MAP_LOG, std::ofstream::out | std::ofstream::trunc);
    logFile.close();

    // Open game_state.txt in write mode to clear its contents
    std::ofstream stateFile(MARIO_LOG, std::ofstream::out | std::ofstream::trunc);
    stateFile.close();
}