#include "GUI.h"
GUI::GUI()
{
	init();
}

GUI::~GUI()
{
	delete label_coins;
	delete label_lives;
	delete label_time_remaining;
	delete label_score;
	delete exit_button;
	delete statusScreen;
	delete heartIcon;
	delete coinIcon;
	delete gameOver;
}

Label *GUI::createLabel()
{
	return new Label();
}

void GUI::init()
{
	this->label_coins = createLabel();
	this->label_coins->setPosition(350.0f, GUI_HEIGHT);

	sf::IntRect coinRect(32, 86, 40, 32);
	coinIcon = new MenuObject(ITEM, 280.0f, GUI_HEIGHT, coinRect, 2.0f, 2.0f);

	this->label_lives = createLabel();
	this->label_lives->setPosition(120.0f, GUI_HEIGHT);

	sf::IntRect heartRect(0, 0, 38, 100);
	heartIcon = new MenuObject(HEART_ICON, 40.0f, -50.f, heartRect, 2.0f, 2.0f);

	this->label_time_remaining = createLabel();
	this->label_time_remaining->setPosition(800.0f, GUI_HEIGHT);

	this->label_score = createLabel();
	this->label_score->setPosition(550.0f, GUI_HEIGHT);

	exit_button = new MenuObject(EXIT_BUTTON, 900.0f, 5.0f);
	exit_button->setScale(0.1f, 0.1f);

	statusScreen = new StatusScreen(new MenuObject(LUIGI, 230.0f, 510.0f), new MenuObject(MARIO, 360.0f, 510.0f), createLabel(), createLabel());

	gameOver = createLabel();
	this->gameOver->setPosition(400.0f, 400.0f);
	gameOver->setString("GAME OVER");
}

void GUI::setCoin(int numCoin)
{
	std::stringstream str_stream;
	str_stream << "x" << std::setw(2) << std::setfill('0') << numCoin;
	label_coins->setString(str_stream.str());
}

void GUI::setLives(int numLives)
{
	label_lives->setString("x" + std::to_string(numLives));
}

void GUI::setTimeRemaining(int time)
{
	std::stringstream str_stream;
	str_stream << "TIME\n"
				  << std::setw(3) << std::setfill('0') << time;
	label_time_remaining->setString(str_stream.str());
}

void GUI::setScore(int score)
{
	std::stringstream str_stream;
	str_stream << "SCORE\n"
				  << std::setw(6) << std::setfill('0') << score;
	label_score->setString(str_stream.str());
}

void GUI::setStatus(int numLives, int level)
{
	statusScreen->setLabelLevel(level);
	statusScreen->setLabelLives(numLives);
}

void GUI::draw(sf::RenderWindow &w)
{
	label_coins->draw(w);
	label_lives->draw(w);
	label_time_remaining->draw(w);
	label_score->draw(w);
	exit_button->draw(w);
	coinIcon->draw(w);
	heartIcon->draw(w);
}

void GUI::drawStatus(sf::RenderWindow &w)
{
	statusScreen->draw(w);
}

void GUI::drawGameOver(sf::RenderWindow &w)
{
	gameOver->draw(w);
}

bool GUI::handleClicking(sf::RenderWindow &w)
{
	if (exit_button->isMouseOver(w))
	{
		MarioGameManager::getInstance()->togglePause();
		MarioGameManager::getInstance()->setState(MarioGameManager::GameState::menu);
		MarioGameManager::getInstance()->getMenuManager()->setMenuState(MenuManager::eMainMenu);
		return true;
	}
	return false;
}

Label::Label()
{
	if (!font.loadFromFile("resource/Minecraft.ttf"))
	{
	}
	text.setFont(font);
	text.setCharacterSize(40);				 // Set character size (in pixels)
	text.setFillColor(sf::Color::White); // Set text color
	text.setStyle(sf::Text::Bold);
}

void Label::setString(const std::string &str)
{
	text.setString(str);
}

void Label::setPosition(float x, float y)
{
	text.setPosition(x, y);
}

void Label::draw(sf::RenderWindow &w)
{
	w.draw(text);
}

StatusScreen::StatusScreen(MenuObject *marioIcon, MenuObject *luigiIcon, Label *label_lives, Label *label_level)
{
	this->marioIcon_status = marioIcon;
	this->marioIcon_status->setTextureRect(sf::IntRect(0, 96, 28, 32));
	this->marioIcon_status->setScale(2, 2);
	this->luigiIcon_status = luigiIcon;
	this->luigiIcon_status->setTextureRect(sf::IntRect(0, 96, 28, 32));
	this->luigiIcon_status->setScale(-2, 2);

	this->label_lives = label_lives;
	this->label_lives->setPosition(475.0f, 500.0f);

	this->label_level = label_level;
	this->label_level->setPosition(400.0f, 400.0f);
}

StatusScreen::~StatusScreen()
{
	delete marioIcon_status;
	delete luigiIcon_status;
	delete label_level;
	delete label_lives;
}

void StatusScreen::setLabelLives(int numLives)
{
	label_lives->setString("x" + std::to_string(numLives));
}

void StatusScreen::setLabelLevel(int level)
{
	std::stringstream str_stream;
	str_stream << "LEVEL"
				  << std::setw(2) << level;
	label_level->setString(str_stream.str());
}

void StatusScreen::draw(sf::RenderWindow &w)
{
	marioIcon_status->draw(w);
	luigiIcon_status->draw(w);
	label_level->draw(w);
	label_lives->draw(w);
}
