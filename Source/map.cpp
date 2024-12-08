#include "map.h"

Map::Map()
{
    blocktexture.loadFromFile("Images/TilesBackup.png");
    block.setTexture(blocktexture);
    readmap();
}

// read map organization from a file
// the map file contains 3 layers: the first layer for blocks, the second layer for background details, the third layer for entity spawns
// corresponding numbers for certain objects will be shown below
void Map::readmap()
{
    projectionmap.clear();
    backgroundmap.clear();
    int height, width;
    int coordinates;
    std::ifstream mapfile("Data/maps.txt");
    mapfile >> height >> width;
    int count = width;
    for (int i = 0; i < height * width; i++)
    {
        mapfile >> coordinates;
        if (count == width)
        {
            count = 0;
            projectionmap.push_back(vector<int>({}));
        }
        projectionmap[projectionmap.size() - 1].push_back(coordinates);
        count++;
    }
    count = width;
    for (int i = 0; i < height * width; i++)
    {
        mapfile >> coordinates;
        if (count == width)
        {
            count = 0;
            backgroundmap.push_back(vector<int>({}));
        }
        backgroundmap[backgroundmap.size() - 1].push_back(coordinates);
        count++;
    }
    for (int i = 0; i < height * width; i++)
    {
        mapfile >> coordinates;
        if (count == width)
        {
            count = 0;
            entitymap.push_back(vector<int>({}));
        }
        entitymap[entitymap.size() - 1].push_back(coordinates);
        count++;
    }
}

// draw a map.
// Note that for every map, the last 3 blocks from either side will not be accessible.
// So in order to create future maps, please spare the last 3 columns for blank background
void Map::draw(sf::RenderWindow &w, int MarioX, int MarioY)
{
    // int xstart, ystart = 0, xtex, ytex, offset;
    // if (MarioX <= 8 * BLOCK_WIDTH)
    // {
    //     xstart = 0;
    //     offset = 0;
    // }
    // else if (MarioX > 78 * BLOCK_WIDTH)
    // {
    //     xstart = 59;
    //     offset = 0;
    // }
    // else
    // {
    //     xstart = MarioX / BLOCK_WIDTH - 8;
    //     offset = MarioX % BLOCK_WIDTH;
    // }
    // for (int i = 0; i < 15; i++)
    // {
    //     for (int j = xstart; j < xstart + 21; j++)
    //     {
    //         block.setTextureRect(IntRect(1 * BLOCK_WIDTH, 7 * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT));
    //         block.setPosition((j - (xstart + 3)) * BLOCK_WIDTH - offset, i * BLOCK_HEIGHT);
    //         w.draw(block);
    //         block.setTexture(blocktexture);
    //         switch (backgroundmap[i][j])
    //         {
    //         case 0: // sky
    //             xtex = 1;
    //             ytex = 7;
    //             break;
    //         case 10: // cloud
    //             if (i == 0)
    //                 ytex = 5;
    //             else if (backgroundmap[i - 1][j] != 10)
    //                 ytex = 5;
    //             else
    //                 ytex = 6;
    //             if (backgroundmap[i][j - 1] != 10)
    //                 xtex = 2;
    //             else if (backgroundmap[i][j + 1] != 10)
    //                 xtex = 4;
    //             else
    //                 xtex = 3;
    //             break;
    //         default:
    //             break;
    //         }
    //         block.setTextureRect(IntRect(xtex * BLOCK_WIDTH, ytex * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT));
    //         block.setPosition((j - (xstart + 3)) * BLOCK_WIDTH - offset, i * BLOCK_HEIGHT);
    //         w.draw(block);
    //         switch (projectionmap[i][j])
    //         {
    //         case 0: // nothing
    //             break;
    //         case 1: // wall
    //             xtex = 1;
    //             ytex = 0;
    //             break;
    //         case 2: // mystery box
    //             xtex = 2;
    //             ytex = 1;
    //             break;
    //         case 3: // vertical up pipe
    //             if (projectionmap[i][j - 1] != 3)
    //             {
    //                 if (i == 0)
    //                 {
    //                     xtex = 6;
    //                     ytex = 2;
    //                     break;
    //                 }
    //                 else if (projectionmap[i - 1][j] != 3)
    //                 {
    //                     xtex = 6;
    //                     ytex = 1;
    //                     break;
    //                 }
    //                 else
    //                 {
    //                     xtex = 6;
    //                     ytex = 2;
    //                     break;
    //                 }
    //             }
    //             else
    //             {
    //                 if (i == 0)
    //                 {
    //                     xtex = 7;
    //                     ytex = 1;
    //                     break;
    //                 }
    //                 else if (projectionmap[i - 1][j] != 3)
    //                 {
    //                     xtex = 7;
    //                     ytex = 1;
    //                     break;
    //                 }
    //                 else
    //                 {
    //                     xtex = 7;
    //                     ytex = 2;
    //                 }
    //             }
    //             break;
    //         case 4: // horizontal left-ward pipe
    //             if (i == 0)
    //                 ytex = 3;
    //             else if (projectionmap[i - 1][j] != 4)
    //                 ytex = 3;
    //             else
    //                 ytex = 4;
    //             if (projectionmap[i][j - 1] != 4)
    //                 xtex = 4;
    //             else
    //                 xtex = 5;
    //             break;
    //         case 7: // mushroom tile, not mushroom buff
    //             ytex = 0;
    //             if (projectionmap[i][j - 1] != 7)
    //                 xtex = 4;
    //             else if (projectionmap[i][j + 1] != 7)
    //                 xtex = 6;
    //             else
    //                 xtex = 5;
    //             break;
    //         default:
    //             break;
    //         }
    //         block.setTextureRect(IntRect(xtex * BLOCK_WIDTH, ytex * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT));
    //         block.setPosition((j - (xstart + 3)) * BLOCK_WIDTH - offset, i * BLOCK_HEIGHT);
    //         w.draw(block);
    //     }
    // }
}

vector<vector<int>> Map::getmap(int option)
{
    switch (option)
    {
    case 0:
        return projectionmap;
    default:
        return entitymap;
    }
}

void Map::createblock(int x, int y)
{
    if (projectionmap[y][x] == 0) return;
    Entity* block = new Entity;
    RenderManager::GetInstance().listEntity.push_back(block);
    block->scaleX = 1.0;
    block->scaleY = 1.0;
    block->xPos = (x - 5) * BLOCK_WIDTH;
    block->yPos = y * BLOCK_HEIGHT;
    block->name = "Block";
    SpriteRenderer* sr = AddComponent<SpriteRenderer>(block);
    sr->layer = 1;
    sr->texture.loadFromFile("Images/TilesBackup.png");
    sr->texture.setSmooth(true);
    sr->sprite.setTexture(sr->texture);
    int xtex, ytex;
    switch (projectionmap[y][x])
    {
    case 0: // nothing
        xtex = 1;
        ytex = 7;
        break;
    case 1: // wall
        xtex = 1;
        ytex = 0;
        break;
    case 2: // mystery box
        xtex = 2;
        ytex = 1;
        break;
    case 3: // vertical up pipe
        if (projectionmap[y][x - 1] != 3)
        {
            if (y == 0)
            {
                xtex = 6;
                ytex = 2;
                break;
            }
            else if (projectionmap[y - 1][x] != 3)
            {
                xtex = 6;
                ytex = 1;
                break;
            }
            else
            {
                xtex = 6;
                ytex = 2;
                break;
            }
        }
        else
        {
            if (y == 0)
            {
                xtex = 7;
                ytex = 1;
                break;
            }
            else if (projectionmap[y - 1][x] != 3)
            {
                xtex = 7;
                ytex = 1;
                break;
            }
            else
            {
                xtex = 7;
                ytex = 2;
            }
        }
        break;
    case 4: // horizontal left-ward pipe
        if (y == 0)
            ytex = 3;
        else if (projectionmap[y - 1][x] != 4)
            ytex = 3;
        else
            ytex = 4;
        if (projectionmap[y][x - 1] != 4)
            xtex = 4;
        else
            xtex = 5;
        break;
    case 7: // mushroom tile, not mushroom buff
        ytex = 0;
        if (projectionmap[y][x - 1] != 7)
            xtex = 4;
        else if (projectionmap[y][x + 1] != 7)
            xtex = 6;
        else
            xtex = 5;
        break;
    default:
        break;
    }
    sr->sprite.setTextureRect(sf::IntRect(xtex * BLOCK_WIDTH, ytex * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT));
    BoxCollider* bc = AddComponent<BoxCollider>(block);
    bc->width = BLOCK_WIDTH;
    bc->height = BLOCK_HEIGHT;
    RigidBody* rb = AddComponent<RigidBody>(block);
    bc->body = rb;
    rb->collider = bc;
    rb->isUsingGravity = false;
    rb->isStatic = true;
    rb->xVel = 0;
    rb->yVel = 0;
}

void Map::blockgenerator(int MarioX, int MarioY)
{
    int xstart = 0, ystart = 0, offset;
    // if (MarioX <= 8 * BLOCK_WIDTH)
    // {
    //     xstart = 0;
    //     offset = 0;
    // }
    // else if (MarioX > 78 * BLOCK_WIDTH)
    // {
    //     xstart = 59;
    //     offset = 0;
    // }
    // else
    // {
    //     xstart = MarioX / BLOCK_WIDTH - 8;
    //     offset = MarioX % BLOCK_WIDTH;
    // }
    for (int i = 0; i < 15; i++)
        for (int j = xstart; j < projectionmap[0].size(); j++) createblock(j, i);
}

// void block::initiate(int x, int y, int blocktype)
// {
//     Entity* block = new Entity;
//     RenderManager::GetInstance().listEntity.push_back(block);
//     block->scaleX = 1.0;
//     block->scaleY = 1.0;
//     block->xPos = x;
//     block->yPos = y;
//     block->name = "Block";
//     blockSprite = AddComponent<SpriteRenderer>(block);
//     blockSprite->layer = 1;
//     blockSprite->texture.loadFromFile("Images/TilesBackup.png");

// }