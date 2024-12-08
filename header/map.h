#ifndef MAP_H
#define MAP_H

#include "mario.h"

class Map
{
private:
    vector<vector<int>> projectionmap;
    vector<vector<int>> backgroundmap;
    vector<vector<int>> entitymap;
    Sprite block;
    Texture blocktexture;

public:
    Map();
    void readmap();
    void draw(RenderWindow &w, int MarioX, int MarioY);
    vector<vector<int>> getmap(int option);
    hitbox gethitbox(int x, int y);
};

#endif