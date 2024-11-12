#include "interface.h"

int main()
{
   // Map map;
   // Mario mario;
   // map.readmap();
   // RenderWindow w(VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "Window", Style::Default);
   // RectangleShape r;
   // r.setSize(Vector2f(200, 200));
   // r.setPosition(-150, 150);
   // r.setFillColor(Color::Red);
   // Event ev;
   // int index = 8 * BLOCK_WIDTH;
   // while (w.isOpen())
   // {
   //    while (w.pollEvent(ev))
   //    {
   //       switch (ev.type)
   //       {
   //       case Event::Closed:
   //          w.close();
   //          break;
   //       case Event::KeyPressed:
   //          if (ev.key.code == Keyboard::A)
   //          {
   //             if (index >= 2) index-= 2;
   //          }
   //          if (ev.key.code == Keyboard::D)
   //          {
   //             if (index <= 59 * BLOCK_WIDTH - 2) index+= 2;
   //          }
   //          break;
   //       }
   //    }
   //    w.clear();
   //    map.draw(w, index, 0);
   //    w.display();
   // }
   interface i;
   i.operate();
   return 0;
}