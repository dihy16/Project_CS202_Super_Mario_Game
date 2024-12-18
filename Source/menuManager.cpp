#include "menuManager.h"
#include "marioGameManager.h"
#include <iostream>
using namespace std;
MenuManager::MenuManager()
{
    menuState = eMainMenu;

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
    setMenuState(static_cast<MenuState>(state));
}
void MenuManager::handleEvents(sf::RenderWindow &window, sf::Event &ev)
{
    
    switch(menuState) {
        case eMainMenu:
            mainMenu->EventHandling(window, ev);
            break;
        case eLevelMenu:
            levelMenu->EventHandling(window, ev);
            break;
        case eGame:
            MarioGameManager::getInstance()->setState(MarioGameManager::GameState::playing);
            break;
    }
}

void MenuManager::draw(sf::RenderWindow& window) {
    switch(menuState) {
        case eMainMenu:
            mainMenu->draw(window);
            break;
        case eLevelMenu:
            levelMenu->draw(window);
            break;
        default:
            break;
    }
}

int MenuManager::getMenuState() {
	return menuState;
}

void MenuManager::setMenuState(MenuState viewID) {
	this->menuState = viewID;
}
