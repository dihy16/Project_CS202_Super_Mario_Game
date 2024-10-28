#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.h"
#include "Map.h"
#include "mario.h"
using namespace std;
using namespace sf;

int main()
{
   Map map;
   map.readmap();
   RenderWindow w(VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "Window", Style::Default);
   RectangleShape r;
   r.setSize(Vector2f(200, 200));
   r.setPosition(-150, 150);
   r.setFillColor(Color::Red);
   Event ev;
   int index = 8 * BLOCK_WIDTH;
   while (w.isOpen())
   {
      while (w.pollEvent(ev))
      {
         switch (ev.type)
         {
         case Event::Closed:
            w.close();
            break;
         case Event::KeyPressed:
            if (ev.key.code == Keyboard::A)
            {
               index-= 5;
            }
            else if (ev.key.code == Keyboard::D)
            {
               index+= 5;
            }
            break;
         }
      }
      w.clear();
      //w.draw(r);
      map.draw(w, index, 0);
      w.display();
   }
   
   return 0;
}