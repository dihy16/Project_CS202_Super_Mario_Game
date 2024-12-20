#include "menuHighscore.h"

void HighscoreMenu::addObserver(IGameStateObserver *observer)
{
    observers.push_back(observer);
}

void HighscoreMenu::removeObserver(IGameStateObserver *observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void HighscoreMenu::notifyObserver(int gameState)
{
    for (const auto &o : observers)
    {
        for (const auto &o : observers)
        {
            o->changeState(gameState);
        }
    }
}

void HighscoreMenu::draw(sf::RenderWindow &w)
{
     Menu::draw(w);
     this->highScoreList = MarioGameManager::getInstance()->getVectorHiScore();
     for (int i = 0; i < 5; i++)
    {
        highscores[i]->setString(std::to_string(highScoreList[i]));
        highscores[i]->draw(w);
    }
}

HighscoreMenu::HighscoreMenu() : highscores(5, nullptr)
{
    isHidden = false;
    this->addMenuOption(new MenuObject(SCOREBOARD_BG, 0.0f, 0.0f));
    this->addMenuOption(new MenuObject(EXIT_BUTTON, 900.0f, 5.0f, 0.1f, 0.1f));

     for (int i = 0; i < 5; i++)
     {
         highscores[i] = new Label(450.0f, 230.0f + 100.0f * i);
     }
}

HighscoreMenu::~HighscoreMenu()
{
    for (int i = 0; i < 5; i++)
    {
        delete highscores[i];
    }
}

void HighscoreMenu::handleClicking(sf::RenderWindow &window)
{
    int indexButPressed = this->getButClicked(window);
    switch (indexButPressed)
    {
    case 1:
        notifyObserver(MenuManager::eMainMenu); // to Select Character Screen
        break;
    default:
        break;
    }
}
