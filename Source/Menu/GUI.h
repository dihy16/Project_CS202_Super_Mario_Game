#ifndef GUI_H
#define GUI_H

#include "./../definition.h"
#include "MenuObject.h"
#include "marioGameManager.h"

class MarioGameManager;

class Label : public MenuObject
{
private:
	sf::Text text;
	sf::Font font;

public:
	Label();
	Label(int size, sf::Color color, bool isBold);
	Label(const std::string &str, float x, float y);
	Label(int size, sf::Color color, bool isBold, float x, float y);
	Label(const std::string &str, int size, sf::Color color, bool isBold, float x, float y);
	Label(float x, float y);
	void setString(const std::string &str);
	void setPosition(float x, float y);
	void draw(sf::RenderWindow& window) const override;
	std::string getString() override
	{
		return text.getString().toAnsiString();
	}
};

class StatusScreen : public Menu
{
private:
	enum MenuObjName {
		characterIcon,
		labelLevel,
		labelLives
	};

public:
	StatusScreen();
	void setLabelLives(int numLives);
	void setLabelLevel(int level);
	void setCharIcon(bool isMarioSelected);
	void handleClicking(sf::RenderWindow &window);
};

class PlayerWinScreen : public Menu
{
private:
	enum MenuObjName {
		playerWinText,
		playerScoreText,
		int_PlayerScore
	};

public:
	PlayerWinScreen();
	void setLabelPlayerScore(int numScore);
	void handleClicking(sf::RenderWindow &window);
};

class GUI // handles UI in the game screen
{
private:
	const float GUI_HEIGHT = 20.0f;
	Label *label_coins;
	Label *label_lives;
	Label *label_time_remaining;
	Label *label_score;
	MenuObject *exit_button;
	MenuObject *heartIcon;
	MenuObject *coinIcon;

	StatusScreen *statusScreen;
	Label *gameOver;
	PlayerWinScreen* playerWinScreen;

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
	void drawGameOver(sf::RenderWindow &w);
	void drawPlayerWin(sf::RenderWindow& w);
	bool handleClicking(sf::RenderWindow &w);
	void setPlayerWinScore(int score);
	void setCharIcon(bool isMarioSelected);
	std::string getStringCoins()
	{
		return label_coins->getString();
	}
};
#endif