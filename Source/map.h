#pragma once

// #include "mario.h"
#include <fstream>
#include "enemy.h"

class Map
{
private:
    vector<vector<int>> projectionmap;
    vector<vector<int>> backgroundmap;
    vector<vector<int>> entitymap;
    int xstart, ystart, offset;
    sf::Texture blocktexture;
    std::vector<Entity *> availableblocks;
    sf::Image layout;
public:
    bool left = false, right = false;
    Map();
    Map(std::string file);
    void readmap();
    void readmap(std::string file);
    void draw(sf::RenderWindow &w, int MarioX, int MarioY);
    vector<vector<int>> getmap(int option);
    int getblockstate(int x, int y)
    {
        return projectionmap[y][x];
    }
    // function creates a list of block entities
    void createblock(int marioX, int marioY);
    void blockgenerator(int, int);
    // function checks for entity availability within map sight
    // map nudge functions, default 5 pixels
    void moveleft(float step);
    void moveright(float step);
};

// class block: public Entity
// {
// private:
//     SpriteRenderer* blockSprite;
//     BoxCollider* hitbox;
//     RigidBody* hitboxbody;
//     sf::Texture texture;
// public:
//     block(float x, float y): xPos(x), yPos(y){}
//     void initiate(int, int, int);
// };