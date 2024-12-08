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

typedef enum
{
   GOOMBA,
   KOOPA_TROOPA,
   HAMMER_BRO,
   LAKITU,
   SPINY,
   PIRANHA_PLANT,
} EnemyType;

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
   Area()
   {
      width = 0;
      height = 0;
   }
   Area(int w, int h)
   {
      width = w;
      height = h;
   }
};

struct Position
{
   float x; // left
   float y; // top
   Position()
   {
      x = 0;
      y = 0;
   }
   Position(int left, int top)
   {
      x = left;
      y = top;
   }
};

struct hitbox
{
   Position position;
   Area size;
   hitbox(int left, int top, int xwidth, int xheight)
   {
      position.x = left;
      position.y = top;
      size.height = xheight;
      size.width = xwidth;
   }
};

bool in(Position, hitbox);

bool hit(hitbox, hitbox);

#define BLOCK_WIDTH 64
#define BLOCK_HEIGHT 64
#define GRAVITY 120

#define MARIO "resource/Mario.png"
#define MARIO_SUPER "resource/MarioSuper.png"
#define ENEMY "resource/Enemies.png"