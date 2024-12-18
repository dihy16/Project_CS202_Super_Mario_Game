#include "marioGameManager.h"

MarioGameManager *MarioGameManager::instance = nullptr;
MarioGameManager::GameState MarioGameManager::gameState = MarioGameManager::GameState::menu;

MarioGameManager::MarioGameManager()
{
    menuManager = new MenuManager();
    GUIManager = new GUI();
}

MarioGameManager *MarioGameManager::getInstance()
{
    if (instance == nullptr)
    {
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

GUI *MarioGameManager::getGUI()
{
    return this->GUIManager;
}

void MarioGameManager::updateGUI()
{
    getGUI()->setCoin(marioCoins);
    getGUI()->setLives(marioLives);
    getGUI()->setTimeRemaining(timeRemaining / 1000);
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

void MarioGameManager::addScore()
{
}

void MarioGameManager::addCoin()
{
    ++marioCoins;
    getGUI()->setCoin(marioCoins);
}

void MarioGameManager::setState(GameState gameState)
{
    this->gameState = gameState;
}

void MarioGameManager::updateGameState(int delta_time)
{
    switch (gameState)
    {
    case GameState::playing:
        timeRemaining -= delta_time;
        break;
    }
}

int MarioGameManager::getLives() { return marioLives; }
int MarioGameManager::getCoins() { return marioCoins; }
int MarioGameManager::getScore() { return score; }
int MarioGameManager::getTimeRemaining() { return timeRemaining; }

void MarioGameManager::setLives(int lives) { marioLives = lives; }
void MarioGameManager::setCoins(int coins) { marioCoins = coins; }
void MarioGameManager::setScore(int score) { this->score = score; }
void MarioGameManager::setTimeRemaining(int time) { timeRemaining = time; }
