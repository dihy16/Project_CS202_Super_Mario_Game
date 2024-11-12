#include "interface.h"

interface::interface()
{
    map.readmap();
}

void interface::draw()
{
    map.draw(w, 96, 0);
    //theman.draw(w);
}

void interface::operate()
{
    int index = 8 * BLOCK_WIDTH;
    while (w.isOpen())
    {
        while (w.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                w.close();
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    if (index >= 5) index-= 5;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    if (index <= 59 * BLOCK_WIDTH - 5) index+= 5;
                }
                break;
            }
        }
        w.clear();
        map.draw(w, index, 0);
        w.display();
    }
}