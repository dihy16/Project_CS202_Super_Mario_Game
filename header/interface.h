#pragma once

#include "map.h"

class interface
{
private:
    RenderWindow w{VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "Window", Style::Default};
    Event ev;
    Mario theman{100, 12 * BLOCK_WIDTH};
    Map map;

public:
    interface();
    void draw();
    void operate();
};