#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

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

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 960

#define MARIO "resource/Mario.png"
#define MARIO_SUPER "resource/MarioSuper.png"