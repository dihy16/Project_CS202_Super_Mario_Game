#ifndef LEVELMENU_H
#define LEVELMENU_H
#include "mainMenu.h"

class LevelMenu : public Menu 
{
private:
	// MenuObject oBackGround;
	// MenuObject oEasy;
	// MenuObject oMedium;
	// MenuObject oHard;
	// std::vector<MenuObject*> menuOptions;
    std::vector<IGameStateObserver*> observers; // List of observers
public:

	bool isHidden;
	void addObserver(IGameStateObserver* observer);
	void removeObserver(IGameStateObserver* observer);
	void notifyObserver(int gameState);
	LevelMenu();
	void handleClicking(sf::RenderWindow& window);
};
#endif