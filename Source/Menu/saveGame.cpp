#include "saveGame.h"

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
   std::ofstream logFile(MAP_LOG, std::ios::app);
   if (logFile.is_open())
   {
      logFile << event << " " << xPos << " " << yPos << "\n";
      logFile.close();
   }
   else
      // std::cerr << "Unable to open log file\n";
      RenderManager::GetInstance().debugText += "Unable to open log file";
}
void saveGame(const GameStateMemento &state, const std::string &file)
{
   std::cout << "save game" << std::endl;
   std::ofstream outFile(file);
   if (!outFile)
      // std::cerr << "Unable to open log file\n";
      RenderManager::GetInstance().debugText += "Unable to open log file";

   outFile << state.marioState.name << " " << state.marioState.xPos << " " << state.marioState.yPos
           << " " << state.marioState.lives << " " << state.marioState.coins << " "
           << state.marioState.time << " " << state.marioState.state << "\n";
   outFile.close();
}