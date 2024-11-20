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

int interface::mariomapcollide()
{
    Position m = theman.getPosition();
    
    float x = m.x / (float)BLOCK_WIDTH, y = m.y / (float) BLOCK_HEIGHT;
    hitbox characterbox = theman.gethixbox(), topleft(floor(x) * BLOCK_WIDTH, floor(y) * BLOCK_HEIGHT, BLOCK_HEIGHT, BLOCK_WIDTH), topright((floor(x) + 1) * BLOCK_WIDTH, floor(y) * BLOCK_HEIGHT, BLOCK_HEIGHT, BLOCK_WIDTH), botleft(floor(x) * BLOCK_WIDTH, (floor(y) + 1) * BLOCK_HEIGHT, BLOCK_HEIGHT, BLOCK_WIDTH), botright((floor(x) + 1) * BLOCK_WIDTH, (floor(y) + 1) * BLOCK_HEIGHT, BLOCK_HEIGHT, BLOCK_WIDTH);
    int mapstate = 0, mariostate = 0;
    if (map.getblockstate(floor(x), floor(y))) mapstate++;
    if (map.getblockstate(floor(x) + 1, floor(y))) mapstate += 2;
    if (map.getblockstate(floor(x), floor(y) + 1)) mapstate += 4;
    if (map.getblockstate(floor(x) + 1, floor(y) + 1)) mapstate += 8;
    if (hit(characterbox, topleft)); mariostate++;
    if (hit(characterbox, topright)); mariostate+=2;
    if (hit(characterbox, botleft)); mariostate+=4;
    if (hit(characterbox, botright)); mariostate+=8;
    int collisiontag = mapstate & mariostate;
    return collisiontag;
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
        theman.draw(w, mariomapcollide());
        w.display();
    }
}