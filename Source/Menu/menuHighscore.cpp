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
        o->changeState(gameState);
    }
}

void HighscoreMenu::draw(sf::RenderWindow &w)
{
     Menu::draw(w);
     this->highScoreList = MarioGameManager::getInstance()->getVectorHiScore();
     for (int i = 0; i < highScoreList.size(); i++)
    {
        highscores[i]->setString(score_to_str(highScoreList[i].score));
        timestamps[i]->setString(removeHyphen(highScoreList[i].time));
        highscores[i]->draw(w);
        timestamps[i]->draw(w);
    }
    w.draw(time_text);
    w.draw(score_text);
}

HighscoreMenu::HighscoreMenu() : highscores(5, nullptr), timestamps(5, nullptr)
{
    isHidden = false;
    initText("TIME AND DATE", time_text, sf::Color::White, menuFont, 190.0f, 200.0f);
    initText("SCORE", score_text,sf::Color::White, menuFont, 650.0f, 200.0f);
    this->addMenuOption(new MenuObject(SCOREBOARD_BG, 0.0f, 0.0f));
    this->addMenuOption(new MenuObject(EXIT_BUTTON, 900.0f, 5.0f, 0.1f, 0.1f));

     for (int i = 0; i < TOTAL_HIGHSCORES; i++)
     {
        highscores[i] = new Label(40, sf::Color::Black, false, 660.0f, 250.0f + 40.0f * i);
        timestamps[i] = new Label(40, sf::Color::Black, false, 195.0f, 250.0f + 40.0f * i);
     }
}

HighscoreMenu::~HighscoreMenu()
{
    for (int i = 0; i < 5; i++)
    {
        delete highscores[i];
        delete timestamps[i];
    }
}

void HighscoreMenu::handleClicking(sf::RenderWindow &window)
{
    int indexButPressed = this->getButClicked(window);
    switch (indexButPressed)
    {
    case 1:
        notifyObserver(MenuManager::eMainMenu); 
        break;
    default:
        break;
    }
}

