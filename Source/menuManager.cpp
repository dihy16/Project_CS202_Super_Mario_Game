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
    if (ev.type == sf::Event::MouseButtonReleased)
        cout << "mouse released" << endl;
    if (ev.type == sf::Event::MouseButtonPressed)
        cout << "mouse pressed" << endl;
    if (menuState == eMainMenu) {
        mainMenu->EventHandling(window, ev);
    }
    else if (menuState == eLevelMenu) {
        levelMenu->EventHandling(window, ev);
    }
    if (menuState == eGame) {
        MarioGameManager::getInstance()->loadLevel(false);
        MarioGameManager::getInstance()->setState(MarioGameManager::GameState::playing);
    }
    else if (menuState == eSavedGame) {
        //MarioGameManager::getInstance()->loadLevel(true);
        MarioGameManager::getInstance()->setState(MarioGameManager::GameState::playing);
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
