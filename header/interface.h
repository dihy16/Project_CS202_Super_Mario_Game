#pragma once

#include "map.h"
#include <cmath>

class interface
{
private:
    RenderWindow w{VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "Window", Style::Default};
    Event ev;
    Mario theman{8 * BLOCK_WIDTH, 12 * BLOCK_HEIGHT};
    Map map;

public:
    interface();
    void draw();
    void operate();
    int mariomapcollide();
};