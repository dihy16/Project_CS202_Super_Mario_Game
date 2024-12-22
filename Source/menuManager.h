#ifndef MenuManager_H
#define MenuManager_H

#include "mainMenu.h"
#include "levelMenu.h"
#include "menuHighscore.h"
#include "menuSettings.h"

class MainMenu;
class LevelMenu;
class CharacterMenu;
class MarioGameManager;
class MainMenu;
class HighscoreMenu;
class MenuSettings;

class MenuManager : public IGameStateObserver
{
private:
	MainMenu *mainMenu;
	LevelMenu *levelMenu;
	CharacterMenu *characterMenu;
	HighscoreMenu *highscoreMenu;
	MenuSettings *menuSettings;
public:
	// Define pages number
	enum MenuState
	{
		eMainMenu,
		eLevelMenu,
		eCharacterMenu,
		eGame,
		eSavedGame,
		eInstruction,
		eSettings,
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
