#ifndef MARIOGAMEMANAGER_H
#define MARIOGAMEMANAGER_H

#include "gameManager.h"
#include "menuManager.h" 
#include "PhysicsEngine/Managers/RenderManager.h"
#include "mario.h"  
#include "GUI.h"
#include "enemy.h"
#include "items.h"
#include "map.h"

class Mario;
class Map;
class Item;
class Enemy;

class Level
{
private:
    Mario* mario;
    Map* m;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Item>> items;
    sf::Image entitylayout;
public:
    bool display, finished;
    Level(int level);
    void handleKeyPress();
    void start();
    void end();
    void execute();
    void drawLevel();
};

class MarioGameManager : public GameManager {
private:
    static MarioGameManager* instance;
    MenuManager* menuManager;   
    GUI* GUIManager;
    Level* lv1;
    int marioLives = 3;
	int score = 0;
	int marioCoins = 0;
    int timeRemaining = 300000;
    std::string currentLevel;
    sf::Clock timer;
    // GameScene* currentScene = nullptr;
    // std::vector<GameScene*> sceneStack;
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
    GameState getState() { return gameState; }
    void updateGameState(int delta_time, sf::Event& ev); // delta time in milliseconds
    void marioDies();
    int loadLevel(const std::string& level_name);
    void togglePause();
};

class GameScene {
private:
    // Level* currentLevel = nullptr;
public:
    GameScene();
};

#endif