#include "mainMenu.h"
#include <iostream>
using namespace std;

#define MAIN_MENU_BG "resource/Menu/MainMenuBG.png"
#define NEW_GAME_BUT "resource/Menu/NewGameBut.png"
#define SETTINGS_BUT "resource/Menu/SettingsBut.png"
#define SCORE_BUT "resource/Menu/ScoreBut.png"
#define H2P_BUT "resource/Menu/H2PBut.png"

MainMenu::MainMenu()
{
    // menuOptions[0] = new MenuObject(MAIN_MENU_BG,0.0f,0.0f);
    this->addMenuOption(new MenuObject(MAIN_MENU_BG, 0.0f, 0.0f));
    this->addMenuOption(new MenuObject(NEW_GAME_BUT, 252.0f, 306.0f));
    this->addMenuOption(new MenuObject(H2P_BUT, 252.0f, 428.0f));
    this->addMenuOption(new MenuObject(SCORE_BUT, 252.0f, 550.0f));
    this->addMenuOption(new MenuObject(SETTINGS_BUT, 252.0f, 672.0f));

    // MenuObject* o1 = new MenuObject;
    // o1->init(MAIN_MENU_BG, 0.0f, 0.0f);
    // addMenuOption(o1);
    // MenuObject* o2 = new MenuObject;
    // o2->init(NEW_GAME_BUT, 252.0f, 306.0f);
    // addMenuOption(o2);
    // MenuObject* o3 = new MenuObject;
    // o3->init(H2P_BUT, 252.0f, 428.0f);
    // addMenuOption(o3);
    // MenuObject* o4 = new MenuObject;
    // o4->init(SCORE_BUT, 252.0f, 550.0f);
    // addMenuOption(o4);
    // MenuObject* o5 = new MenuObject;
    // o5->init(SETTINGS_BUT, 252.0f, 672.0f);
    // addMenuOption(o5);
    //
    //  oBackGround.init(MAIN_MENU_BG,0.0f,0.0f);
    //  oNewGame.init(NEW_GAME_BUT,252.0f,306.0f);
    //  oH2P.init(H2P_BUT,252.0f,428.0f);
    //  oScore.init(SCORE_BUT,252.0f,550.0f);
    //  oSettings.init(SETTINGS_BUT,252.0f,672.0f);

    // menuOptions.push_back()

    isHidden = false;
}

void MainMenu::addObserver(IGameStateObserver *observer)
{
    observers.push_back(observer);
}

void MainMenu::removeObserver(IGameStateObserver *observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void MainMenu::notifyObserver(int gameState)
{
    for (const auto &o : observers)
    {
        o->changeState(gameState);
    }
}

void MainMenu::handleClicking(sf::RenderWindow &window)
{
    int indexButPressed = this->getButClicked(window);
    cout << indexButPressed << endl;
    switch (indexButPressed)
    {
    case 1:                // oNewGame
        notifyObserver(1); // to Level Menu
        break;
    case 2:
        // MarioGameManager::getInstance()->setCurrentLevel(1);
        notifyObserver(3);
        break;
    default:
        break;
    }
    // if (oBackGround.isMouseOver(window)) {
    //     notifyObserver(1);
    // }
    // else if (oSettings.isMouseOver(window)) {

    // }
    // else if (oScore.isMouseOver(window)) {

    // }
    // else if (oH2P.isMouseOver(window)) {

    // }
}
