#include "marioGameManager.h"

MarioGameManager* MarioGameManager::instance = nullptr;
MarioGameManager::GameState MarioGameManager::gameState = MarioGameManager::GameState::menu;

MarioGameManager::MarioGameManager()
{
    menuManager = new MenuManager();
    GUIManager = new GUI();

    for (const char* sound : { "breakblock", "bump", "coin", "fireball", "jump_super", "kick", "stomp","powerup_appears",
         "powerup", "pipe","flagpole", "bowser_falls", "bowser_fire", "mario_die","stage_clear",
         "game_over","1-up","warning", "world_clear","pause","beep","fireworks" })
        getSoundBufferManager().loadFromFile(sound, std::string("resource/Sound/") + sound + ".wav");

    for (const char* music : { "overworld", "underworld", "bowsercastle", "underwater", "invincibility" })
        getMusicManager().loadFromFile(music, std::string("resource/Music/") + music + ".ogg");
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
    getGUI()->setCoin(marioCoins);
    playSound("1-up");
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




