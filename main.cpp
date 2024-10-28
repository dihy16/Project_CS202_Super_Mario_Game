#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.h"
#include "Map.h"
using namespace std;
using namespace sf;

int main()
{
   Map map;
   
   // RenderWindow w(VideoMode(16 * BLOCK_WIDTH, 15 * BLOCK_HEIGHT), "Window", Style::Default);
   // RectangleShape r;
   // r.setSize(Vector2f(200, 200));
   // r.setPosition(150, 150);
   // r.setFillColor(Color::Red);
   // Event ev;
   // int index = 0;
   // while (w.isOpen())
   // {
   //    while (w.pollEvent(ev))
   //    {
   //       switch (ev.type)
   //       {
   //       case Event::Closed:
   //          w.close();
   //          break;
   //       case Event::MouseButtonPressed:
   //          if (ev.mouseButton.button == Mouse::Left)
   //          {
   //             index++;
   //             cout << "Index: " << index << endl;
   //          }
   //          break;
   //       }
   //    }
   //    w.clear();
   //    w.draw(r);
   //    w.display();
   // }
   map.readmap();
   return 0;
}