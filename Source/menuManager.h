#ifndef  MenuManager_H
#define MenuManager_H


#include "mainMenu.h"
#include "levelMenu.h"

class LevelMenu;
class MainMenu;
class MarioGameManager;

class MenuManager : public IGameStateObserver {
private:
    MainMenu* mainMenu;
	LevelMenu* levelMenu;
public:
    // Define pages number
	enum MenuState {
		eMainMenu,
		eLevelMenu,
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
    void handleEvents(sf::RenderWindow& window, sf::Event& ev);
    void draw(sf::RenderWindow& window);
    int getMenuState();
	void setMenuState(MenuState viewID);
};
#endif // ! MenuManager_H
