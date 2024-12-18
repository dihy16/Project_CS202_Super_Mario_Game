#ifndef LEVEL_H
#define LEVEL_H
#include "mario.h"
#include "enemy.h"
#include "items.h"
#include "map.h"
#include <random>

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
#endif