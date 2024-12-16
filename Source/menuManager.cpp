#include "menuManager.h"
#include "marioGameManager.h"
#include <iostream>
using namespace std;
MenuManager::MenuManager()
{
    currentGameState = eMainMenu;

    mainMenu = new MainMenu();
    levelMenu = new LevelMenu();
    mainMenu->addObserver(this);
    levelMenu->addObserver(this);
}

MenuManager::~MenuManager()
{
    delete mainMenu;
    delete levelMenu;
}

void MenuManager::changeState(int state)
{
    setGameState(static_cast<gameState>(state));
}
void MenuManager::handleEvents(sf::RenderWindow &window, sf::Event &ev)
{
    
    switch(currentGameState) {
        case eMainMenu:
            mainMenu->EventHandling(window, ev);
            break;
        case eLevelMenu:
            levelMenu->EventHandling(window, ev);
            break;
        case eGame:
            MarioGameManager::getInstance()->setState(MarioGameManager::GameState::playing);
            MarioGameManager::getInstance()->playMusic(MarioGameManager::overworld);
            break;
    }
}

void MenuManager::draw(sf::RenderWindow& window) {
    switch(currentGameState) {
        case eMainMenu:
            mainMenu->draw(window);
            break;
        case eLevelMenu:
            levelMenu->draw(window);
            break;
        case eGame:
            RenderManager::GetInstance().Update();
            MarioGameManager::getInstance()->updateGUI();
            MarioGameManager::getInstance()->getGUI()->draw(window);
            //RenderManager::GetInstance().debugConsole.setString("Game");
            break;
    }
}

int MenuManager::getGameState() {
	return currentGameState;
}

void MenuManager::setGameState(gameState viewID) {
	this->currentGameState = viewID;
}
