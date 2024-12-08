#include "../header/definition.h"

bool in(Position point, hitbox box)
{
	cout << box.position.x << " " << box.position.x + box.size.width - 1 << " " << point.x << '\n';
	if (box.position.x > point.x || point.x > box.position.x + box.size.width - 1)
	{
		cout << "!\n";
		return false;
	}
	cout << box.position.y << " " << box.position.y + box.size.height - 1 << " " << point.y << '\n';
	if (box.position.y > point.y || point.y > box.position.y + box.size.height - 1)
	{
		cout << "!\n";
		return false;
	}
	return true;
}

bool hit(hitbox box1, hitbox box2)
{
	if (box1.position.x + box1.size.width - 1 < box2.position.x) return false;
	if (box2.position.x + box2.size.width - 1 < box1.position.x) return false;
	if (box1.position.y + box1.size.height - 1 < box2.position.y) return false;
	if (box2.position.y + box2.size.height - 1 < box1.position.y) return false;
	return true;

}