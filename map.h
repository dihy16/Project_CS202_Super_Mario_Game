#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "define.h"

class map
{
private:
    std::vector<std::vector<int>> intprojectionmap;
    sf::Sprite block;
    int x, y;
};