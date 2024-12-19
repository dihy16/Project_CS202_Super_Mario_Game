#ifndef LEVEL_H
#define LEVEL_H
#include "character.h"
#include "enemy.h"
#include "items.h"
#include "map.h"
#include <random>
#include "saveGame.h"

class Mario;
class Luigi;
class Map;
class Item;
class Enemy;
class Flag: public Entity
{
private:
public:
    Flag(){}
};
class MarioGameManager;
class GameStateMemento;

class Level
{
private:
    // Mario *mario;
    // Luigi *luigi;
    Mario *mario;
    Map *m;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Item>> items;
    sf::Image entitylayout;
    Flag* f = nullptr;
    int lv;
    sf::Clock timer;

public:
    bool display, finished;
    Level(int level, bool resuming);
    ~Level();
    void handleKeyPress();
    void start();
    void end();
    void execute();
    void drawLevel();
    GameStateMemento saveMarioState();
};
#endif