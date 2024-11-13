#include "./header/mario.h"
#include <SFML/Graphics.hpp>

int main()
{
   RenderWindow w(VideoMode(1200, 900), "Mario Game", Style::Default);
   w.setFramerateLimit(60);
   Event e;

   Mario mario(100, 500);
   while (w.isOpen())
   {
      while (w.pollEvent(e))
      {
         switch (e.type)
         {
         case Event::Closed:
            w.close();
            break;
         default:
            mario.handleEvents(e);
            break;
         }
      }
      w.clear();
      mario.draw(w);
      w.display();
   }
   return 0;
}