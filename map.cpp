#include "Map.h"

Map::Map()
{
    blocktexture.loadFromFile("Images/Tiles.png");
}

void Map::readmap()
{
    int height, width;
    std::string coordinates;
    std::ifstream mapfile("Data/maps.txt");
    mapfile >> height >> width;
    std::cout << height << " " << width << '\n';
    while (mapfile >> coordinates) std::cout << coordinates << '\n';
}