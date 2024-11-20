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
   float x; //left
   float y; //top
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
hitbox(int left, int top, int xheight, int xwidth)
{
   position.x = left;
   position.y = top;
   size.height = xheight;
   size.width = xwidth;
}
};

bool in(Position point, hitbox box)
{
   if (box.position.x > point.x || point.x > box.position.x + box.size.width) return false;
   if (box.position.y > point.y || point.y > box.position.y + box.size.height) return false;
   return true;
}

bool hit(hitbox box1, hitbox hit2)
{
   Position topleft(hit2.position.x, hit2.position.y), topright(hit2.position.x + hit2.size.width, hit2.position.y), botleft(hit2.position.x, hit2.position.y + hit2.size.height), botright(hit2.position.x + hit2.size.width, hit2.position.y + hit2.size.height);
   return in(topleft, box1) || in(topright, box1) || in(botleft, box1) || in(botright, box1);
}

#define BLOCK_WIDTH 64
#define BLOCK_HEIGHT 64

#define MARIO "resource/Mario.png"
#define MARIO_SUPER "resource/MarioSuper.png"