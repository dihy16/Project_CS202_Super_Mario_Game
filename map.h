#pragma once

// #include <vector>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.h"

class Map
{
private:
    std::vector<std::vector<int>> intprojectionmap;
    sf::Sprite block;
    sf::Texture blocktexture;
public:
    Map();
    void readmap();
    void draw(sf::RenderWindow& w, int x, int y);
};