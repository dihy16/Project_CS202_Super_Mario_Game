#include "LevelMenu.h"
#include <iostream>
using namespace std;

#define DIFFICULTY_BG "resource/Menu/Difficulty/DifficultyBG.png"
#define PEACEFUL_BUT "resource/Menu/Difficulty/PeacefulBut.png"
#define EASY_BUT "resource/Menu/Difficulty/EasyBut.png"
#define MEDIUM_BUT "resource/Menu/Difficulty/MediumBut.png"
#define EXPERT_BUT "resource/Menu/Difficulty/ExpertBut.png"
#define MASTER_BUT "resource/Menu/Difficulty/MasterBut.png"

LevelMenu::LevelMenu()
{
    // oBackGround.init(DIFFICULTY_BG,0.0f,0.0f);
    // oEasy.init();
    // oMedium.init();
    // oHard.init();
    this->addMenuOption(new MenuObject(DIFFICULTY_BG, 0.0f, 0.0f));
    this->addMenuOption(new MenuObject(EASY_BUT, 276.0f, 330.0f));
    this->addMenuOption(new MenuObject(MEDIUM_BUT, 276.0f, 444.0f));
    this->addMenuOption(new MenuObject(EXPERT_BUT, 276.0f, 558.0f));
}

void LevelMenu::addObserver(IGameStateObserver *observer)
{
    observers.push_back(observer);
}

void LevelMenu::removeObserver(IGameStateObserver *observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void LevelMenu::notifyObserver(int gameState)
{
    for (const auto &o : observers)
    {

        o->changeState(gameState);
    }
}
void LevelMenu::handleClicking(sf::RenderWindow &window)
{
    int indexButPressed = this->getButClicked(window);
    cout << "but clicked: " << indexButPressed << endl;
    switch (indexButPressed)
    {
    case 1: // Easy
        MarioGameManager::getInstance()->setCurrentLevel(1);
        notifyObserver(MenuManager::eCharacterMenu); // to Game Screen
        break;
    case 2:
        MarioGameManager::getInstance()->setCurrentLevel(2);
        notifyObserver(MenuManager::eCharacterMenu);
        break;
    case 3:
        MarioGameManager::getInstance()->setCurrentLevel(3);
        notifyObserver(MenuManager::eCharacterMenu);
        break;
    default:
        break;
    }
    cout << "out handle clicking" << endl;
}


// ***** CHARACTER MENU SECTION *****


void CharacterMenu::addObserver(IGameStateObserver *observer)
{
    observers.push_back(observer);
}

void CharacterMenu::removeObserver(IGameStateObserver *observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void CharacterMenu::notifyObserver(int gameState)
{
    for (const auto &o : observers)
    {
        for (const auto &o : observers)
        {
            o->changeState(gameState);
        }
    }
}

CharacterMenu::CharacterMenu()
{
    isHidden = false;
    sf::IntRect spriteRect(0, 96, 28, 32);
    this->addMenuOption(new MenuObject(SOUND_CONTROLS_BG, 0, 0));
    this->addMenuOption(new Label("SELECT CHARACTER", 40, sf::Color(255, 250, 255), true, 281.0f, 251.0f));
    this->addMenuOption(new MenuObject(MARIO, 330.0f, 480.0f, spriteRect, 2.2f, 2.2f));
    this->addMenuOption(new MenuObject(LUIGI, 630.0f, 480.0f, spriteRect, -2.2f, 2.2f));
    this->addMenuOption(new Label("MARIO", 32, sf::Color(255, 57, 57), true, 310.0f, 430.0f));
    this->addMenuOption(new MenuObject(ARROW, 315.0f, 326.0f));
    this->addMenuOption(new Label("Our main character", 32, sf::Color(255, 250, 255), false, 230.0f, 570.0f));
    this->addMenuOption(new Label("LUIGI", 32, sf::Color(105, 255, 111), true, 610.0f, 430.0f));
    this->addMenuOption(new MenuObject(ARROW, 615.0f, 326.0f));
    this->addMenuOption(new Label("Luigi jumps higher\n but runs slower", 32, sf::Color(255, 250, 255), false, 520.0f, 570.0f));

    for (int i = 6; i < numOfMenuOptions; ++i) {
        menuOptions[i]->hide();
    }
}

void CharacterMenu::handleClicking(sf::RenderWindow &window)
{
    int indexButPressed = this->getButClicked(window);
    cout << "but clicked: " << indexButPressed << endl;
    switch (indexButPressed)
    {
    case 2: // Mario
        MarioGameManager::getInstance()->setIsMarioSelected(true);
        MarioGameManager::getInstance()->getGUI()->setCharIcon(true);
        notifyObserver(MenuManager::MenuState::eGame); // to Game Screen
        break;
    case 3: // Luigi
        MarioGameManager::getInstance()->setIsMarioSelected(false);
        MarioGameManager::getInstance()->getGUI()->setCharIcon(false);
        notifyObserver(MenuManager::MenuState::eGame);
        break;
    default:
        break;
    }
}

void CharacterMenu::handleHovering(sf::RenderWindow &window)
{
    menuOptions[2]->updateColorOnHover(window);
    menuOptions[3]->updateColorOnHover(window);
    int i = 4;
    for (; i <= 6; ++i) {
        menuOptions[i]->updateFromTarget(window, menuOptions[2]);
    }
    for (; i <= 9; ++i) {
        menuOptions[i]->updateFromTarget(window, menuOptions[3]);
    }
}
