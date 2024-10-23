#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
   RenderWindow w(VideoMode(500, 500), "Window", Style::Default);
   RectangleShape r;
   r.setSize(Vector2f(200, 200));
   r.setPosition(150, 150);
   r.setFillColor(Color::Red);
   Event ev;
   while (w.isOpen())
   {
      while (w.pollEvent(ev))
      {
         switch (ev.type)
         {
         case Event::Closed:
            w.close();
            break;
         }
      }
      w.clear();
      w.draw(r);
      w.display();
   }
   return 0;
}
