#include "../header/menuObject.h"

MenuObject::MenuObject(std::string filename, float x, float y) {
    isHidden = false;
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}


void MenuObject::init(std::string filename, float x, float y)
{
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void MenuObject::draw(sf::RenderWindow& window) const
{
    if (!isHidden)
        window.draw(sprite);
}

bool MenuObject::isMouseOver(sf::RenderWindow& window) const
{
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;

    float buttonX = sprite.getPosition().x;
    float buttonY = sprite.getPosition().y;

    return (mouseX >= buttonX && mouseX <= buttonX + sprite.getGlobalBounds().width) && (mouseY >= buttonY && mouseY <= buttonY + sprite.getGlobalBounds().height);
}

void MenuObject::updateColorOnHover(sf::RenderWindow &window)
{
    if (isMouseOver(window)) {
        sprite.setColor(sf::Color(150, 150, 100));
    }
    else {
        sprite.setColor(sf::Color(255, 255, 255));
    }
}
