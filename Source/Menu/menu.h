#ifndef MENU_H
#define MENU_H

#include <vector>
#include "menuObject.h"
#include <sstream>
#include <iomanip>
class Menu
{
protected:
	std::vector<MenuObject *> menuOptions;

	int activeMenuOption;
	int numOfMenuOptions;

public:
	Menu();
	~Menu();
	void addMenuOption(MenuObject *menuOption);
	virtual void draw(sf::RenderWindow &window);
	virtual void handleHovering(sf::RenderWindow &window);
	virtual void handleClicking(sf::RenderWindow &window) = 0;
	virtual int getButClicked(sf::RenderWindow &window);
	virtual void EventHandling(sf::RenderWindow &window, sf::Event &ev);
	std::string score_to_str(int score);
    void initText(const std::string& str, sf::Text& t, sf::Color color, sf::Font& font, float x, float y);
    std::string removeHyphen(const std::string &dateTime);
};

#endif