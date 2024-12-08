#pragma once
#include "mainMenu.h"
#include "levelMenu.h"

class MenuManager : public IGameStateObserver {
private:
    MainMenu* mainMenu;
	LevelMenu* levelMenu;
public:
    // Define pages number
	enum gameState {    
		eMainMenu,
		eLevelMenu,
		eGame,
		eInstruction,
		eOptions,
		eScoreboard,
		// ePause,
	};
    gameState currentGameState;
    MenuManager();
    ~MenuManager();
	void changeState(int gameState);
    void handleEvents(sf::RenderWindow& window, sf::Event& ev);
    void draw(sf::RenderWindow& window);
    int getGameState();
	void setGameState(gameState viewID);
};