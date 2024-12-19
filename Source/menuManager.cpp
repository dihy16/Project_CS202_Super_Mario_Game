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
    if (menuState == eMainMenu)
    {
        mainMenu->EventHandling(window, ev);
    }
    else if (menuState == eLevelMenu)
    {
        levelMenu->EventHandling(window, ev);
    }
    if (menuState == eGame)
    {
        MarioGameManager::getInstance()->loadLevel(false);
        MarioGameManager::getInstance()->setState(MarioGameManager::GameState::status);
    }
    else if (menuState == eSavedGame)
    {
        // MarioGameManager::getInstance()->loadLevel(true);
        MarioGameManager::getInstance()->setState(MarioGameManager::GameState::status);
    }
}

void MenuManager::draw(sf::RenderWindow &window)
{
    switch (menuState)
    {
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

int MenuManager::getMenuState()
{
    return menuState;
}

void MenuManager::setMenuState(MenuState viewID)
{
    this->menuState = viewID;
}
