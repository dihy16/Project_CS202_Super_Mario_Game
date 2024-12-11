#include "mario.h"
#include "enemy.h"
#include "items.h"
#include "map.h"

class Level1
{
private:
   Mario mario;
   Map m;
   std::vector<std::unique_ptr<Enemy>> enemies;
   std::vector<std::unique_ptr<Item>> items;

public:
   bool display, finished;
   Level1();
   void start();
   void end();
};