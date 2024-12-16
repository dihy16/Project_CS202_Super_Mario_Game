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
    void initScoreMap();
public:
    enum ScoreID {
        Coin,
        Mushroom,
        Flower,
        Star
    };
    std::map<ScoreID, int> scoreMap;
	static enum class GameState {menu, pause, playing, levelOver, gameOver} gameState;
    static MarioGameManager* getInstance();
    ~MarioGameManager();
    MenuManager* getMenuManager();
    GUI* getGUI();
    void updateGUI();
    void run();
    void draw(sf::RenderWindow& w);
    void handleEvents(sf::RenderWindow& w, sf::Event& ev);
	void addScore(ScoreID scoreId);
    void addCoin();
    void addLive();
    void setState(GameState gameState);
    void updateGameState(int delta_time); // delta time in milliseconds
};

#endif