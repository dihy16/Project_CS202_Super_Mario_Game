#pragma once

// #include <vector>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.h"

class Map
{
private:
    std::vector<std::vector<std::string>> projectionmap;
    sf::Sprite block;
    sf::Texture blocktexture;
public:
    Map();
    void readmap();
    void draw(sf::RenderWindow& w, int MarioX, int MarioY);
};