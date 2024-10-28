#include "Map.h"

Map::Map()
{
    blocktexture.loadFromFile("Images/TilesBackup.png");
    block.setTexture(blocktexture);
}

//read map organization from a file
//every block will be stored in the format XY, with X and Y be the respective coordinates of the sprite in Tiles.png
//10 will be stored by A
void Map::readmap()
{
    projectionmap.clear();
    int height, width;
    std::string coordinates;
    std::ifstream mapfile("Data/maps.txt");
    mapfile >> height >> width;
    int count = width;
    while (mapfile >> coordinates)
    {
        if (count == width)
        {
            count = 0;
            projectionmap.push_back(std::vector<std::string>({}));
        }
        projectionmap[projectionmap.size() - 1].push_back(coordinates);
        count++;
    }
}

//draw a map.
//Note that for every map, the last 3 blocks from either side will not be accessible.
//So in order to create future maps, please spare the last 3 columns for blank background
void Map::draw(sf::RenderWindow& w, int MarioX, int MarioY)
{
    int xstart, ystart = 0, xtex, ytex, offset;
    if (MarioX < 3 * BLOCK_WIDTH)
    {
        xstart = 0;
        offset = 0;
    }
    else if (MarioX > 78 * BLOCK_WIDTH)
    {
        xstart = 59;
        offset = 0;
    }
    else
    {
        xstart = MarioX / BLOCK_WIDTH - 3;
        offset = MarioX % BLOCK_WIDTH;
    }
    std::cout << xstart << '\n';
    for (int i = 0; i < 15; i++)
    {
        for (int j = xstart; j < xstart + 21; j++)
        {
            if (projectionmap[i][j][0] == 'A') ytex = 10;
            else ytex = projectionmap[i][j][0] - 48;
            xtex = projectionmap[i][j][1] - 48;
            block.setTexture(blocktexture);
            block.setTextureRect(sf::IntRect(xtex * BLOCK_WIDTH, ytex * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT));
            block.setPosition((j - (xstart + 3)) * BLOCK_WIDTH - offset, i * BLOCK_HEIGHT);
            w.draw(block);
        }
    }
}

