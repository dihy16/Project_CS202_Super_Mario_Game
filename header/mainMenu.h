#pragma once

#include "menu.h"
#include "menuObserver.h"

class MainMenu : public Menu 
{
private:
	// MenuObject oBackGround;
	// MenuObject oNewGame;
	// MenuObject oSettings;
	// MenuObject oScore;
	// MenuObject oH2P;
	//std::vector<MenuObject*> menuOptions;
    std::vector<IGameStateObserver*> observers; // List of observers
public:

	bool isHidden;
	void addObserver(IGameStateObserver* observer);
	void removeObserver(IGameStateObserver* observer);
	void notifyObserver(int gameState);
	MainMenu();
	// void draw(sf::RenderWindow& window);
	void handleClicking(sf::RenderWindow& window);
	// void handleHovering(sf::RenderWindow& window);
	// void EventHandling(sf::RenderWindow& window, sf::Event& ev);
};
