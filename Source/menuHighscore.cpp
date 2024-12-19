#include "menuHighscore.h"

void MenuHighscore::addObserver(IGameStateObserver *observer)
{
    observers.push_back(observer);
}

void MenuHighscore::removeObserver(IGameStateObserver *observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void MenuHighscore::notifyObserver(int gameState)
{
    for (const auto &o : observers)
    {
        for (const auto &o : observers)
        {
            o->changeState(gameState);
        }
    }
}

MenuHighscore::MenuHighscore()
{
}
