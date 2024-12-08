#ifndef MARIOGAMEMANAGER_H
#define MARIOGAMEMANAGER_H

#include "gameManager.h"
#include "menuManager.h" 

class MarioGameManager : public GameManager {
private:
    static MarioGameManager* instance;
    MenuManager* menuManager;   
    int marioLives = 3;
	int score = 0;
	int marioCoins = 0;
    std::string currentLevel;
    MarioGameManager();
public:
	static enum class GameState {menu, status, playing, levelOver, gameOver} gameState;
    MarioGameManager* getInstance();
    ~MarioGameManager();
    MenuManager* getMenuManager();
    void run();
    void draw(sf::RenderWindow& w);
    void handleEvents(sf::RenderWindow& w, sf::Event& ev);
    void addScore();
    void addCoin();
    void setState(GameState gameState);
};

#endif