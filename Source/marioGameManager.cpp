#include "marioGameManager.h"

// Map* MarioGameManager::map = new Map();
// Mario* MarioGameManager::theman = new Mario(8 * BLOCK_WIDTH, 12 * BLOCK_HEIGHT);
MarioGameManager* MarioGameManager::instance = nullptr;
MarioGameManager::MarioGameManager()
{
    // map->readmap();
    menuManager = new MenuManager();
    getMusicManager().loadFromFile("overworld", "resource/Music/overworld.ogg");
}

MarioGameManager *MarioGameManager::getInstance()
{
    if (this->instance == nullptr) {
        this->instance = new MarioGameManager();
    }
    return this->instance;
}

MarioGameManager::~MarioGameManager()
{
    // delete map;
    delete menuManager;
    // delete theman;
}

void MarioGameManager::run()
{
}
void MarioGameManager::draw(sf::RenderWindow &w)
{
    menuManager->draw(w);
}

void MarioGameManager::handleEvents(sf::RenderWindow &w, sf::Event &ev)
{
    menuManager->handleEvents(w, ev);
    // theman->handleEvents(ev);
}

// Map *MarioGameManager::getMap()
// {
//     return map;
// }

// Mario *MarioGameManager::getMario()
// {
//     return theman;
// }

void MarioGameManager::setState(GameState gameState)
{
    this->gameState = gameState;
}
