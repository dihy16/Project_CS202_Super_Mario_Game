#ifndef MARIOGAMEMANAGER_H
#define MARIOGAMEMANAGER_H

#include "gameManager.h"
#include "menuManager.h"
#include "PhysicsEngine/Managers/RenderManager.h"
#include "character.h"
#include "GUI.h"
#include "level.h"
#include "saveGame.h"

class Level;
class LevelMenu;
class MainMenu;
class MenuHighscore;
class MenuSettings;
class MenuManager;
class GUI;

struct HighScoreEntry
{
    int score;
    std::string time;
};

class MarioGameManager : public GameManager
{
private:
    static MarioGameManager *instance;
    MenuManager *menuManager;
    GUI *GUIManager;
    Level *level;
    int marioLives = 3;
    int score = 0;
    int marioCoins = 0;
    int timeRemaining = 300000;
    int currentLevel;
    sf::Clock timer;
    // GameScene* currentScene = nullptr;
    // std::vector<GameScene*> sceneStack;
    bool isMarioSelected = true;
    MarioGameManager();
    void initScoreMap();

    vector<HighScoreEntry> vHighscore;
    friend class MenuManager;

public:
    enum ScoreID
    {
        Coin,
        Mushroom,
        Flower,
        Star,
        Goomba,
        Koopa
    };
    std::map<ScoreID, int> scoreMap;
    static enum class GameState { menu,
                                  pause,
                                  status,
                                  playing,
                                  levelOver,
                                  gameOver } gameState;
    static MarioGameManager *getInstance();
    ~MarioGameManager();
    MenuManager *getMenuManager();
    GUI *getGUI();
    Level *getLevel();
    void updateGUI();
    void run();
    void draw(sf::RenderWindow &w);
    void handleEvents(sf::RenderWindow &w, sf::Event &ev);
    void addScore(ScoreID scoreId);
    void addCoin();
    void addLive();
    void setState(GameState gameState);
    int getLives();
    int getCoins();
    int getScore();
    int getTimeRemaining();
    void setLives(int lives);
    void setCoins(int coins);
    void setScore(int score);
    void setTimeRemaining(int time);
    void setIsMarioSelected(bool isMarioSelected);
    GameState getState() { return gameState; }
    void updateGameState(int delta_time, sf::Event &ev); // delta time in milliseconds
    void marioDies();
    void loadLevel(bool resuming, bool isMario = true);
    void togglePause();
    int getCurrentLevel();
    void setCurrentLevel(int currentLevel);
    // void saveHiScore();
    void loadHiScore();
    const std::vector<HighScoreEntry> &getVectorHiScore();
    std::string getStringCurrentTime();
    void updateHighScores(int newScore, const std::string &time);
};

class GameScene
{
private:
    // Level* currentLevel = nullptr;
public:
    GameScene();
};

#endif