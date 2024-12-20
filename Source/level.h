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
    Flag *f = nullptr;
    int lv;
    sf::Clock timer;

public:
    bool isMario, finished;
    Level(int level, bool resuming, bool isMario);
    ~Level();
    void handleKeyPress();
    void start();
    void end();
    void execute();
    void drawLevel();
    GameStateMemento saveMarioState();
};
#endif