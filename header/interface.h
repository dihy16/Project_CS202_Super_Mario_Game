#pragma once

#include "marioGameManager.h"

class interface
{
private:
    RenderWindow w{VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "Window", Style::Default};
    Event ev;
    MarioGameManager* mGameManager;
public:
    // interface();
    // void draw();
    void operate();
};