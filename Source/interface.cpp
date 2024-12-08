#include "../header/interface.h"
#include <iostream>
using namespace std;
// interface::interface()
// {
//     map.readmap();
// }

// void interface::draw()
// {
//     map.draw(w, 96, 0);
//     // theman.draw(w);
// }

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
                mGameManager->handleEvents(w, ev);
                break;
            }
        }
        w.clear();
        mGameManager->draw(w);
        w.display();
    }
}