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
}

Label* GUI::createLabel()
{
	return new Label();
}

void GUI::init()
{
	this->label_coins = createLabel();
	this->label_coins->setPosition(350.0f, 10.0f);
	this->label_lives = createLabel();
	this->label_lives->setPosition(100.0f, 10.0f);
	this->label_time_remaining = createLabel();
	this->label_time_remaining->setPosition(700.0f, 10.0f);
}

void GUI::setCoin(int numCoin)
{
	std::stringstream str_stream;
	str_stream << "x" << std::setw(2) << std::setfill('0') << numCoin;
	label_coins->setString(str_stream.str());
}

void GUI::setLives(int numLives)
{
	label_lives->setString(" x " + std::to_string(numLives));
}

void GUI::setTimeRemaining(int time)
{
	std::stringstream str_stream;
	str_stream << "TIME\n" << std::setw(3) << std::setfill('0') << time;
	label_time_remaining->setString(str_stream.str());
}

void GUI::draw(sf::RenderWindow& w)
{
	label_coins->draw(w);
	label_lives->draw(w);
	label_time_remaining->draw(w);
}

Label::Label()
{
	if (!font.loadFromFile("resource/Minecraft.ttf"))
	{
	}
	text.setFont(font);
	text.setCharacterSize(40);           // Set character size (in pixels)
	text.setFillColor(sf::Color::White); // Set text color
	text.setStyle(sf::Text::Bold);      
}

void Label::setString(const std::string& str)
{
	text.setString(str);
}

void Label::setPosition(float x, float y)
{
	text.setPosition(x, y);
}

void Label::draw(sf::RenderWindow& w)
{
	w.draw(text);
}
