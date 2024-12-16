#include "marioGameManager.h"

MarioGameManager* MarioGameManager::instance = nullptr;
MarioGameManager::GameState MarioGameManager::gameState = MarioGameManager::GameState::menu;

MarioGameManager::MarioGameManager()
{
    menuManager = new MenuManager();
    GUIManager = new GUI();
    initScoreMap();
}

void MarioGameManager::initScoreMap()
{
    scoreMap[Coin] = 200;
    scoreMap[Mushroom] = 1000;
    scoreMap[Flower] = 1000;
    scoreMap[Star] = 1000;
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
    delete GUIManager;
    delete instance;
}

MenuManager *MarioGameManager::getMenuManager()
{
    return this->menuManager;
}

GUI* MarioGameManager::getGUI()
{
    return this->GUIManager;
}

void MarioGameManager::updateGUI()
{
    getGUI()->setCoin(marioCoins);
    getGUI()->setLives(marioLives);
    getGUI()->setTimeRemaining(timeRemaining / 1000);
    getGUI()->setScore(score);
}

void MarioGameManager::run()
{
    setState(GameState::menu);
}
void MarioGameManager::draw(sf::RenderWindow &w)
{
    menuManager->draw(w);
}

void MarioGameManager::handleEvents(sf::RenderWindow &w, sf::Event &ev)
{
    menuManager->handleEvents(w, ev);
}

void MarioGameManager::addScore(ScoreID scoreId)
{
    score += scoreMap[scoreId];
}

// Map *MarioGameManager::getMap()
// {
//     return map;
// }

// Mario *MarioGameManager::getMario()
// {
//     return theman;
// }

void MarioGameManager::addCoin()
{
    ++marioCoins;
    if (marioCoins >= 40) {
        marioCoins = 0;
        addLive();
    }
    // addScore(ScoreID::Coin);
    // getGUI()->setCoin(marioCoins);
}

void MarioGameManager::addLive()
{
    ++marioLives;
}

void MarioGameManager::setState(GameState gameState)
{
    this->gameState = gameState;
}

void MarioGameManager::updateGameState(int delta_time)
{
    switch (gameState) {
    case GameState::playing:
        timeRemaining -= delta_time;
        break;
    }
}




