#include "../header/definition.h"

bool in(Position point, hitbox box)
{
   if (box.position.x > point.x || point.x > box.position.x + box.size.width - 1) return false;
   if (box.position.y > point.y || point.y > box.position.y + box.size.height - 1) return false;
   return true;
}

bool hit(hitbox box1, hitbox hit2)
{
   Position topleft(hit2.position.x, hit2.position.y), topright(hit2.position.x + hit2.size.width - 1, hit2.position.y), botleft(hit2.position.x, hit2.position.y + hit2.size.height - 1), botright(hit2.position.x + hit2.size.width - 1, hit2.position.y + hit2.size.height - 1);
   return in(topleft, box1) || in(topright, box1) || in(botleft, box1) || in(botright, box1);
}