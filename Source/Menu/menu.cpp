#include "menu.h"
#include <iostream>
using namespace std;

Menu::Menu(void)
{
	this->activeMenuOption = 0;
	this->numOfMenuOptions = 0;
	if (!menuFont.loadFromFile("resource/Minecraft.ttf")) {}
}

Menu::~Menu(void)
{
	for (int i = 0; i < numOfMenuOptions; i++)
	{
		delete menuOptions[i];
	}
}

void Menu::addMenuOption(MenuObject *menuOption)
{
	menuOptions.push_back(menuOption);
	++numOfMenuOptions;
}
// void Menu::updateActiveButton(int iDir) {
void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < numOfMenuOptions; ++i)
	{
		menuOptions[i]->draw(window);
	}
}
// 	switch(iDir) {
void Menu::handleHovering(sf::RenderWindow &window)
{
	int i = 1; // Do not handle hovering on background
	for (; i < numOfMenuOptions; ++i)
	{
		menuOptions[i]->updateColorOnHover(window);
	}
}

int Menu::getButClicked(sf::RenderWindow &window)
{
	int i = 1; // Do not handle clicking on background
	for (; i < numOfMenuOptions; ++i)
	{
		if (menuOptions[i]->isMouseOver(window))
			return i;
	}
	return -1;
}

void Menu::EventHandling(sf::RenderWindow &window, sf::Event &ev)
{
	switch (ev.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::MouseButtonReleased:
		this->handleClicking(window);
		break;
	case sf::Event::MouseMoved:
		handleHovering(window);
		break;
	default:
		break;
	}
}

std::string Menu::score_to_str(int score)
{
    std::stringstream str_stream;
    str_stream << std::setw(6) << std::right << score;
    return str_stream.str();
}

void Menu::initText(const std::string& str, sf::Text& text, sf::Color color, sf::Font& font,float x, float y)
{
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
    text.setPosition(x, y);
    text.setString(str);
}

std::string Menu::removeHyphen(const std::string &dateTime)
{
    std::string formattedDateTime = dateTime;
    size_t pos = std::string::npos;
    int hyphenCount = 0;

    // Find the position of the third hyphen
    for (size_t i = 0; i < formattedDateTime.length(); ++i)
    {
        if (formattedDateTime[i] == '-')
        {
            hyphenCount++;
            if (hyphenCount == 3)
            {
                pos = i;
                break;
            }
        }
    }

    // Replace the third hyphen with a space
    if (pos != std::string::npos)
    {
        formattedDateTime.replace(pos, 1, " ");
    }

    return formattedDateTime;
}
