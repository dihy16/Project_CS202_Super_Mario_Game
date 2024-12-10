#ifndef MENU_H
#define MENU_H

#include <vector>

#include "menuObject.h"

class Menu
{
private:
	std::vector<MenuObject*> menuOptions;

	int activeMenuOption;
	int numOfMenuOptions;

public:
	Menu();
	~Menu();
	void addMenuOption(MenuObject* menuOption);
	virtual void draw(sf::RenderWindow& window);
	virtual void handleHovering(sf::RenderWindow &window);
	virtual void handleClicking(sf::RenderWindow &window) = 0;
	virtual int getButClicked(sf::RenderWindow &window);
	virtual void EventHandling(sf::RenderWindow& window, sf::Event& ev);

	// ----- 0 = TOP, 1 = RIGHT, 2 = BOTTOM, 3 = LEFT
	// virtual void updateActiveButton(int iDir);
};

#endif