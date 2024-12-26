#include "menuManager.h"
#include "marioGameManager.h"
#include <iostream>
using namespace std;
MenuManager::MenuManager()
{
    menuState = eMainMenu;

    mainMenu = new MainMenu();
    levelMenu = new LevelMenu();
    characterMenu = new CharacterMenu();
    menuSettings = new MenuSettings();
    highscoreMenu = new HighscoreMenu();

    mainMenu->addObserver(this);
    levelMenu->addObserver(this);
    characterMenu->addObserver(this);
    menuSettings->addObserver(this);
    highscoreMenu->addObserver(this);
}

MenuManager::~MenuManager()
{
    delete mainMenu;
    delete levelMenu;
    delete characterMenu;
    delete menuSettings;
    delete highscoreMenu;
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
    else if (menuState == eCharacterMenu)
    {
        characterMenu->EventHandling(window, ev);
    }
    else if (menuState == eSettings)
    {
        menuSettings->EventHandling(window, ev);
    }
    else if (menuState == eScoreboard)
    {
        highscoreMenu->EventHandling(window, ev);
    }
    if (menuState == eGame)
    {
        DeleteObjects();
        MarioGameManager::getInstance()->loadLevel(false, MarioGameManager::getInstance()->getIsMarioSelected());
        MarioGameManager::getInstance()->setState(MarioGameManager::GameState::status);
        MarioGameManager::getInstance()->resetGame();
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
    case eCharacterMenu:
        characterMenu->draw(window);
        break;
    case eSettings:
        menuSettings->draw(window);
        break;
    case eScoreboard:
        highscoreMenu->draw(window);
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
    if (this->menuState == eSettings) {
        menuSettings->updateTextureId();
        menuSettings->updateSoundBarTexture();
    }
}
