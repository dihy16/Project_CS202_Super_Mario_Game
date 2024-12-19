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
    this->addMenuOption(new MenuObject(PEACEFUL_BUT, 276.0f, 218.0f));
    this->addMenuOption(new MenuObject(EASY_BUT, 276.0f, 330.0f));
    this->addMenuOption(new MenuObject(MEDIUM_BUT, 276.0f, 444.0f));
    this->addMenuOption(new MenuObject(EXPERT_BUT, 276.0f, 558.0f));
    this->addMenuOption(new MenuObject(MASTER_BUT, 276.0f, 672.0f));
    this->addMenuOption(new MenuObject(DIFFICULTY_BG, 0.0f, 0.0f));
    this->addMenuOption(new MenuObject(PEACEFUL_BUT, 276.0f, 218.0f));
    this->addMenuOption(new MenuObject(EASY_BUT, 276.0f, 330.0f));
    this->addMenuOption(new MenuObject(MEDIUM_BUT, 276.0f, 444.0f));
    this->addMenuOption(new MenuObject(EXPERT_BUT, 276.0f, 558.0f));
    this->addMenuOption(new MenuObject(MASTER_BUT, 276.0f, 672.0f));
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
        for (const auto &o : observers)
        {
            o->changeState(gameState);
        }
    }

    void LevelMenu::handleClicking(sf::RenderWindow & window)
    {
        int indexButPressed = this->getButClicked(window);
        cout << "but clicked: " << indexButPressed << endl;
        switch (indexButPressed)
        {
        case 1: // Easy
            MarioGameManager::getInstance()->setCurrentLevel(1);
            notifyObserver(2); // to Game Screen
            break;
        case 2:
            MarioGameManager::getInstance()->setCurrentLevel(2);
            notifyObserver(2);
            break;
        case 3:
            MarioGameManager::getInstance()->setCurrentLevel(3);
            notifyObserver(2);
            break;
        default:
            break;
        }
        cout << "out handle clicking" << endl;
    }
