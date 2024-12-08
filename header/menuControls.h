#pragma once

#include "menu.h"
#include "menuObserver.h"

class MenuControls : public Menu 
{
private:
	MenuObject oBackGround;
    std::vector<IGameStateObserver*> observers; // List of observers
public:

	bool isHidden;
	void addObserver(IGameStateObserver* observer);
	void removeObserver(IGameStateObserver* observer);
	void notifyObserver(int gameState);
	MenuControls();
	void draw(sf::RenderWindow& window);
	void handleClicking(sf::RenderWindow& window);
	void EventHandling(sf::RenderWindow& window, sf::Event& ev);
};
