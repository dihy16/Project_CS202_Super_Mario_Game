#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "menu.h"
#include "menuObserver.h"
#include "marioGameManager.h"

class MarioGameManager;
class MenuManager;
class MenuHighscore : public Menu
{
private:
    std::vector<IGameStateObserver *> observers;

public:
    bool isHidden;
    void addObserver(IGameStateObserver *observer);
    void removeObserver(IGameStateObserver *observer);
    void notifyObserver(int gameState);
    MenuHighscore();
    void handleClicking(sf::RenderWindow &window);
    // menu
};
#endif