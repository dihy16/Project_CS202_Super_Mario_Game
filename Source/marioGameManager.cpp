#include "marioGameManager.h"

MarioGameManager* MarioGameManager::instance = nullptr;
MarioGameManager::GameState MarioGameManager::gameState = MarioGameManager::GameState::menu;

MarioGameManager::MarioGameManager()
{
    menuManager = new MenuManager();
    getMusicManager().loadFromFile("overworld", "resource/Music/overworld.ogg");
}

MarioGameManager *MarioGameManager::getInstance()
{
    if (instance == nullptr) {
        instance = new MarioGameManager();
    }
    return instance;
}

MarioGameManager::~MarioGameManager()
{
    delete menuManager;
}

MenuManager *MarioGameManager::getMenuManager()
{
    return this->menuManager;
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
