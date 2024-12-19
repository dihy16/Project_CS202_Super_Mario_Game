#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iomanip>
#include <sstream>
#include <string>
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
	void setString(const std::string &str);
	void setPosition(float x, float y);
	void draw(sf::RenderWindow &w);
	std::string getString()
	{
		return text.getString().toAnsiString();
	}
};

class GUI
{
private:
	Label *label_coins;
	Label *label_lives;
	Label *label_time_remaining;
	Label *label_score;
	MenuObject *exit_button;

public:
	GUI();
	~GUI();
	Label *createLabel();
	void init();
	void setCoin(int numCoin);
	void setLives(int numLives);
	void setTimeRemaining(int time);
	void setScore(int score);
	void draw(sf::RenderWindow &w);
	bool handleClicking(sf::RenderWindow &w);
	std::string getStringCoins()
	{
		return label_coins->getString();
	}
};
#endif