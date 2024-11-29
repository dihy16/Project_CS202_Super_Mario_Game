#include "interface.h"

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
    // Position m = theman.getPosition(); //position of Mario, w.r.t his feet
    Position m = theman.getSurroundingPosition();
    // hitbox
    hitbox characterbox = theman.gethixbox();
    float x = m.x, y = m.y;                                                                                                                                                                                                                                                                                                      // where to calculate surrounding blocks
    hitbox topleft(x * BLOCK_WIDTH, y * BLOCK_HEIGHT, BLOCK_HEIGHT, BLOCK_WIDTH), topright((x + 1) * BLOCK_WIDTH, y * BLOCK_HEIGHT, BLOCK_HEIGHT, BLOCK_WIDTH), botleft(x * BLOCK_WIDTH, (y + 1) * BLOCK_HEIGHT, BLOCK_HEIGHT, BLOCK_WIDTH), botright((x + 1) * BLOCK_WIDTH, (y + 1) * BLOCK_HEIGHT, BLOCK_HEIGHT, BLOCK_WIDTH); // surrounding blocks, conditions required later to be fixed
    int mapstate = 0, mariostate = 0;
    // state of the 4 surrounding blocks, either blocked or not
    if (map.getblockstate(x, y))
        mapstate++;
    if (map.getblockstate(x + 1, y))
        mapstate += 2;
    if (map.getblockstate(x, y + 1))
        mapstate += 4;
    if (map.getblockstate(x + 1, y + 1))
        mapstate += 8;
    // where mario stands within those 4 blocks
    if (hit(characterbox, topleft))
        mariostate++;
    if (hit(characterbox, topright))
        mariostate += 2;
    if (hit(characterbox, botleft))
        mariostate += 4;
    if (hit(characterbox, botright))
        mariostate += 8;
    // and the 2 numbers, to reveal which direction collision is happening
    int collisiontag = mapstate & mariostate;
    // to then proceed to collision checking
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
                break;
            }
        }
        theman.animation(w, 0);
        theman.adjustposition(mariomapcollide());
        w.clear();
        map.draw(w, index, 0);
        theman.draw(w, mariomapcollide());
        w.display();
    }
}
