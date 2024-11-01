#include "Entity.h"

int Entity::nextID = 0;

Entity::Entity() : id(nextID++), xPos(0), yPos(0), rotation(0), scaleX(1.f), scaleY(1.f)
{

}

