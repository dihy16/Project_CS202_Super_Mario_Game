#include "saveGame.h"
#include <iostream>
using namespace std;

class CareTaker
{
private:
   std::stack<GameStateMemento> history;

public:
   void saveState(const GameStateMemento &memento)
   {
      history.push(memento);
   }
   bool hasSavedState() const
   {
      return !history.empty();
   }
   GameStateMemento restoreState()
   {
      if (!history.empty())
      {
         GameStateMemento memento = history.top();
         history.pop();
         return memento;
      }
      throw std::runtime_error("No more states to restore");
   }
};
GameStateMemento GameStateMemento::loadState(const std::string &file)
{
   MarioState marioState;
   std::ifstream inFile(file);
   if (inFile.is_open())
   {
      inFile >> marioState;
      inFile.close();
   }
   else
   {
      RenderManager::GetInstance().debugText += "savefile";
      std::cerr << "Unable to open save file\n";
   }
   return GameStateMemento(marioState, std::vector<Entity *>());
}
void logEvent(const std::string &event, float xPos, int yPos)
{
   std::ofstream logFile("Log/game_log.txt", std::ios::app);
   if (logFile.is_open())
   {
      logFile << event << " at (" << xPos << ", " << yPos << ")\n";
      logFile.close();
   }
   else
      std::cerr << "Unable to open log file\n";
}
void saveGame(const GameStateMemento &state, const std::string &file)
{
   cout << "save game" << endl;
   std::ofstream outFile(file);
   if (!outFile)
      std::cerr << "Unable to open log file\n";
   outFile << state.marioState.xPos << " " << state.marioState.yPos << " "
           << state.marioState.lives << " " << state.marioState.coins << " "
           << state.marioState.time << " " << state.marioState.state << "\n";
   outFile.close();
}