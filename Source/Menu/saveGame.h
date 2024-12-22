#ifndef SAVEGAME_H
#define SAVEGAME_H
#include "./../Character/character.h"
#include "./../PhysicsEngine/Entity.h"
class Mario;
struct MarioState
{
   float xPos, yPos;
   int lives, coins, score, time;
   std::string name;
   std::string state;
   friend std::istream &operator>>(std::istream &is, MarioState &state)
   {
      is >> state.name >> state.xPos >> state.yPos >> state.lives >> state.coins >> state.time >> state.state;
      return is;
   }
};
class GameStateMemento
{
public:
   MarioState marioState;
   std::vector<Entity *> entities;
   GameStateMemento(MarioState marioState, std::vector<Entity *> entities) : marioState(marioState), entities(entities) {}
   static GameStateMemento loadState(const std::string &file);
};
void logEvent(const std::string &event, float xPos, int yPos);
void saveGame(const GameStateMemento &state, const std::string &file);
#endif