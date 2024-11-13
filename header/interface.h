#pragma once

#include "map.h"
#include "mario.h"

class interface
{
private:
    sf::RenderWindow w{sf::VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "Window", sf::Style::Default};
    sf::Event ev;
    Mario theman;
    Map map;
public:
    interface();
    void draw();
    void operate();
};