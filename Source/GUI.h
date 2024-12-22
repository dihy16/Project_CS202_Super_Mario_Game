#ifndef GUI_H
#define GUI_H

#include "definition.h"
#include "MenuObject.h"
#include "marioGameManager.h"

class MarioGameManager;

class Label
{
private:
	sf::Text text;
	sf::Font font;

public:
	Label();
	Label(int size, sf::Color color, bool isBold);
	Label(const std::string &str, float x, float y);
	Label(int size, sf::Color color, bool isBold, float x, float y);
	Label(float x, float y);
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
	const float GUI_HEIGHT = 15.0f;
	Label *label_coins;
	Label *label_lives;
	Label *label_time_remaining;
	Label *label_score;
	MenuObject *exit_button;
	MenuObject *heartIcon;
	MenuObject *coinIcon;

	StatusScreen *statusScreen;
	Label *gameOver;

public:
	GUI();
	~GUI();
	static Label *createLabel();
	void init();
	void setCoin(int numCoin);
	void setLives(int numLives);
	void setTimeRemaining(int time);
	void setScore(int score);
	void setStatus(int numLives, int level);
	void draw(sf::RenderWindow &w);
	void drawStatus(sf::RenderWindow &w);
	void drawGameOver(sf::RenderWindow &w);
	void drawExitButton(sf::RenderWindow &w);
	void handleClicking(sf::RenderWindow &w);
	StatusScreen *getStatusScr();
	std::string getStringCoins()
	{
		return label_coins->getString();
	}
};
#endif