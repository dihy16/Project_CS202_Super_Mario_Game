#include "../header/interface.h"

interface::interface()
{
    map.readmap();
}

void interface::draw()
{
    map.draw(w, 96, 0);
    // theman.draw(w);
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
            case Event::Closed:
                w.close();
                break;
            default:
                theman.handleEvents(ev);
                break;
            }
        }

        w.clear();
        map.draw(w, index, 0);
        // theman.draw(w);
        w.display();
    }
}