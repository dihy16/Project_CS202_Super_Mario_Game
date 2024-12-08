#ifndef DEFINITION_H
#define DEFINITION_H

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

bool in(Position, hitbox);

bool hit(hitbox, hitbox);

#define BLOCK_WIDTH 64
#define BLOCK_HEIGHT 64

#define MARIO "resource/Mario.png"
#define MARIO_SUPER "resource/MarioSuper.png"

#define MAIN_MENU_BG "resource/Menu/MainMenuBG.png"
#define NEW_GAME_BUT "resource/Menu/NewGameBut.png"
#define SETTINGS_BUT "resource/Menu/SettingsBut.png"
#define SCORE_BUT "resource/Menu/ScoreBut.png"
#define H2P_BUT "resource/Menu/H2PBut.png"

#define DIFFICULTY_BG "resource/Menu/Difficulty/DifficultyBG.png"
#define PEACEFUL_BUT "resource/Menu/Difficulty/PeacefulBut.png"
#define EASY_BUT "resource/Menu/Difficulty/EasyBut.png"
#define MEDIUM_BUT "resource/Menu/Difficulty/MediumBut.png"
#define EXPERT_BUT "resource/Menu/Difficulty/ExpertBut.png"
#define MASTER_BUT "resource/Menu/Difficulty/MasterBut.png"

#endif