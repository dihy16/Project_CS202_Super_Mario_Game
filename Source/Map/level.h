#ifndef LEVEL_H
#define LEVEL_H
#include "./../Character/character.h"
#include "./../Character/enemy.h"
#include "./../Map/items.h"
#include "./../Map/map.h"
#include <random>
#include "./../Menu/saveGame.h"

class Mario;
class Luigi;
class Map;
class Item;
class Enemy;
class Flag : public Entity
{
private:
public:
    SpriteRenderer *sr;
    BoxCollider *bc;
    RigidBody *rb;
    sf::Clock timer;
    sf::IntRect flagRect;
    int currentRect, maxRect;
    bool finished = false;
    Flag(int x, int y)
    {
        xPos = x;
        yPos = y;
        currentRect = 0, maxRect = 4;
        name = "flag";
        sr = AddComponent<SpriteRenderer>(this);
        sr->layer = 2;
        sr->texture.loadFromFile("resource/Items.png");
        sr->texture.setSmooth(true);
        sr->sprite.setTexture(sr->texture);
        sr->sprite.setTextureRect(sf::IntRect(0, 150, 32, 32));
        sr->sprite.setScale(2, 2);
        bc = AddComponent<BoxCollider>(this);
        bc->width = 0;
        bc->height = 0;
        rb = AddComponent<RigidBody>(this);
        bc->body = rb;
        rb->collider = bc;
        rb->isUsingGravity = false;
        rb->isStatic = true;
        rb->xVel = 0;
        rb->yVel = 0;
        flagRect = sr->sprite.getTextureRect();
    }
    void animation();
};
class MarioGameManager;
class GameStateMemento;

class Level
{
private:
    Luigi *luigi;
    Mario *mario;
    Map *m;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Item>> items;
    sf::Image entitylayout;
    sf::Color c;
    Flag *f = nullptr;
    int lv;
    sf::Clock timer;

public:
    bool isMario, finished;
    Level(int level, bool resuming, bool isMario);
    ~Level();
    void handleKeyPress();
    void loadItems(int level, std::mt19937 &rng, std::uniform_int_distribution<std::mt19937::result_type> &dist1);
    void loadEnemies(int level);
    void end();
    void execute();
    void drawLevel();
    void applyLog(const std::string &log);
    void clearLog();
    GameStateMemento saveMarioState();
};
#endif