#ifndef MARIOGAMEMANAGER_H
#define MARIOGAMEMANAGER_H

#include "gameManager.h"
#include "menuManager.h" 

class MarioGameManager : public GameManager {
private:
    static MarioGameManager* instance;
    // static Mario *theman;
    // static Map* map;
    MenuManager* menuManager;   
	enum class GameState {menu, status, playing, levelOver, gameOver} gameState = GameState::menu;
    int marioLives = 3;
	int score = 0;
	int marioCoins = 0;
    std::string currentLevel;
    MarioGameManager();
public:
    MarioGameManager* getInstance();
    ~MarioGameManager();
    void run();
    void draw(sf::RenderWindow& w);
    void handleEvents(sf::RenderWindow& w, sf::Event& ev);
    // static Map* getMap();
    // static Mario* getMario();
    void addScore();
    void addCoin();
    void setState(GameState gameState);
};

#endif