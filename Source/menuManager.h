#ifndef MenuManager_H
#define MenuManager_H

#include "mainMenu.h"
#include "levelMenu.h"

class MainMenu;
class LevelMenu;
class CharacterMenu;
class MarioGameManager;
class MainMenu;

class MenuManager : public IGameStateObserver
{
private:
	MainMenu *mainMenu;
	LevelMenu *levelMenu;
	CharacterMenu *characterMenu;

public:
	// Define pages number
	enum MenuState
	{
		eMainMenu,
		e,
		eLevelMenu,
		eCharacterMenu,
		eGame,
		eSavedGame,
		eInstruction,
		eOptions,
		eScoreboard,
		// ePause,
	};
	MenuState menuState;
	MenuManager();
	~MenuManager();
	void changeState(int menuState);
	void handleEvents(sf::RenderWindow &window, sf::Event &ev);
	void draw(sf::RenderWindow &window);
	int getMenuState();
	void setMenuState(MenuState viewID);
};
#endif // ! MenuManager_H
