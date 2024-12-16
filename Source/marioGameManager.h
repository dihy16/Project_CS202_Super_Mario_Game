#ifndef MARIOGAMEMANAGER_H
#define MARIOGAMEMANAGER_H

#include "gameManager.h"
#include "menuManager.h" 
#include "PhysicsEngine/Managers/RenderManager.h"
#include "mario.h"  
#include "GUI.h"

class MarioGameManager : public GameManager {
private:
    static MarioGameManager* instance;
    MenuManager* menuManager;   
    GUI* GUIManager;
    int marioLives = 3;
	int score = 0;
	int marioCoins = 0;
    int timeRemaining = 300000;
    std::string currentLevel;
    MarioGameManager();
public:
	static enum class GameState {menu, pause, playing, levelOver, gameOver} gameState;
    static MarioGameManager* getInstance();
    ~MarioGameManager();
    MenuManager* getMenuManager();
    GUI* getGUI();
    void updateGUI();
    void run();
    void draw(sf::RenderWindow& w);
    void handleEvents(sf::RenderWindow& w, sf::Event& ev);
    void addScore();
    void addCoin();
    void setState(GameState gameState);
    void updateGameState(int delta_time); // delta time in milliseconds
};

#endif