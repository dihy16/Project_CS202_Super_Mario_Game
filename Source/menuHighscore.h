#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "menu.h"
#include "menuObserver.h"
#include "marioGameManager.h"
#include "GUI.h"

struct HighScoreEntry;
class MarioGameManager;
class MenuManager;
class Label;
class HighscoreMenu : public Menu
{
private:
    std::vector<IGameStateObserver *> observers;
    sf::Text time_text, score_text;
    std::vector<Label *> highscores;
    std::vector<Label *> timestamps;
    vector<HighScoreEntry> highScoreList;
public:
    bool isHidden;
    void addObserver(IGameStateObserver *observer);
    void removeObserver(IGameStateObserver *observer);
    void notifyObserver(int gameState);
    void draw(sf::RenderWindow &w) override;
    HighscoreMenu();
    ~HighscoreMenu();
    void handleClicking(sf::RenderWindow &window);

    // menu
};
#endif