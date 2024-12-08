#include "menu.h"

Menu::Menu(void) {
	this->activeMenuOption = 0;
	this->numOfMenuOptions = 0;
}

Menu::~Menu(void) {
	for (int i = 0; i < numOfMenuOptions; i++) {
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
	for (int i = 0; i < numOfMenuOptions; ++i) {
		menuOptions[i]->draw(window);
	}
}
// 	switch(iDir) {
void Menu::handleHovering(sf::RenderWindow &window)
{
	int i = 1; // Do not handle hovering on background
	for (; i < numOfMenuOptions; ++i) {
		menuOptions[i]->updateColorOnHover(window);
	}
}

int Menu::getButClicked(sf::RenderWindow &window)
{
	int i = 1; // Do not handle clicking on background
	for (; i < numOfMenuOptions; ++i) {
		if (menuOptions[i]->isMouseOver(window))
			return i;
	}
	return -1;
}

void Menu::EventHandling(sf::RenderWindow &window, sf::Event &ev)
{
	switch (ev.type) {
        case sf::Event::Closed:
            window.close();
        break;
        case sf::Event::MouseButtonPressed:
            this->handleClicking(window);
        break;
        case sf::Event::MouseMoved:
            handleHovering(window);
        break;
    }
}

// 		case 0:
// 			if (activeMenuOption - 1 < 0) {
// 				activeMenuOption = numOfMenuOptions - 1;
// 			} else {
// 				--activeMenuOption;
// 			}
// 			break;
// 		case 2:
// 			if (activeMenuOption + 1 >= numOfMenuOptions) {
// 				activeMenuOption = 0;
// 			} else {
// 				++activeMenuOption;
// 			}
// 			break;
// 		default:
// 			break;
// 	}
// }