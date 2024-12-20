#ifndef LEVELMENU_H
#define LEVELMENU_H
#include "definition.h"
#include "menu.h"
#include "menuObserver.h"
#include "marioGameManager.h"

class MarioGameManager;
class MenuManager;

class LevelMenu : public Menu
{
private:
	std::vector<IGameStateObserver *> observers; // List of observers
public:
	bool isHidden;
	void addObserver(IGameStateObserver *observer);
	void removeObserver(IGameStateObserver *observer);
	void notifyObserver(int gameState);
	LevelMenu();
	void handleClicking(sf::RenderWindow &window);
};

class CharacterMenu : public Menu
{
private:
	std::vector<IGameStateObserver *> observers; // List of observers
public:
	bool isHidden;
	void addObserver(IGameStateObserver *observer);
	void removeObserver(IGameStateObserver *observer);
	void notifyObserver(int gameState);
	CharacterMenu();
	void handleClicking(sf::RenderWindow &window);
};

#endif