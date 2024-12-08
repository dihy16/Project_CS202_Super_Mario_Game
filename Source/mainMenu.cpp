#include "../header/mainMenu.h"
#include <iostream>
using namespace std;
MainMenu::MainMenu() 
{
    // menuOptions[0] = new MenuObject(MAIN_MENU_BG,0.0f,0.0f);
    this->addMenuOption(new MenuObject(MAIN_MENU_BG,0.0f,0.0f));
    this->addMenuOption(new MenuObject(NEW_GAME_BUT,252.0f,306.0f));
    this->addMenuOption(new MenuObject(H2P_BUT,252.0f,428.0f));
    this->addMenuOption(new MenuObject(SCORE_BUT,252.0f,550.0f));
    this->addMenuOption(new MenuObject(SETTINGS_BUT,252.0f,672.0f));
    // oBackGround.init(MAIN_MENU_BG,0.0f,0.0f);
    // oNewGame.init(NEW_GAME_BUT,252.0f,306.0f);
    // oH2P.init(H2P_BUT,252.0f,428.0f);
    // oScore.init(SCORE_BUT,252.0f,550.0f);
    // oSettings.init(SETTINGS_BUT,252.0f,672.0f);

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
    for (const auto& o: observers) {
        o->changeState(gameState);
    }
}

void MainMenu::handleClicking(sf::RenderWindow &window)
{
    int indexButPressed = this->getButClicked(window);
    cout << indexButPressed << endl;
    switch (indexButPressed) {
        case 1: // oNewGame
            notifyObserver(1); // to Level Menu
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
