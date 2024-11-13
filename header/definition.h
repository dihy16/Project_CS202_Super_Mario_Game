#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace sf;

typedef enum
{
   SMALL,
   BIG,
   SUPER
} MarioState;

struct Player
{
   string name;
   string score;
   string level;
   int health;
   int coins;
   float enemiesSpeed;
};

struct Area
{
   float width;
   float height;
};

struct Position
{
   float x;
   float y;
};

#define BLOCK_WIDTH 64
#define BLOCK_HEIGHT 64

#define MARIO "resource/Mario.png"
#define MARIO_SUPER "resource/MarioSuper.png"