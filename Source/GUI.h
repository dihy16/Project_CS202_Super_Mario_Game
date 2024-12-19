#ifndef GUI_H
#define GUI_H

#include "definition.h"
#include "MenuObject.h"
#include "marioGameManager.h"

#define EXIT_BUTTON "resource/Menu/ExitButton.png"
#define MARIO "resource/Mario1.png"

class MarioGameManager;

class Label
{
private:
	sf::Text text;
	sf::Font font;

public:
	Label();
	void setString(const std::string &str);
	void setPosition(float x, float y);
	void draw(sf::RenderWindow &w);
	std::string getString()
	{
		return text.getString().toAnsiString();
	}
};

class StatusScreen
{
private:
	MenuObject *marioIcon_status;
	Label *label_lives;
	Label *label_level;

public:
	StatusScreen(MenuObject *marioIcon_status, Label *label_lives, Label *label_level);
	~StatusScreen();
	void setLabelLives(int numLives);
	void setLabelLevel(int level);
	void draw(sf::RenderWindow &w);
};

class GUI
{
private:
	Label *label_coins;
	Label *label_lives;
	Label *label_time_remaining;
	Label *label_score;
	MenuObject *exit_button;
	MenuObject *marioIcon;
	MenuObject *coinIcon;

	StatusScreen *statusScreen;

public:
	GUI();
	~GUI();
	Label *createLabel();
	void init();
	void setCoin(int numCoin);
	void setLives(int numLives);
	void setTimeRemaining(int time);
	void setScore(int score);
	void setStatus(int numLives, int level);
	void draw(sf::RenderWindow &w);
	void drawStatus(sf::RenderWindow &w);
	bool handleClicking(sf::RenderWindow &w);
	std::string getStringCoins()
	{
		return label_coins->getString();
	}
};
#endif