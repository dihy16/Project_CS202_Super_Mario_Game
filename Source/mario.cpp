#include "../header/mario.h"

Mario::Mario()
{
    normal.loadFromFile("Images/marionormal.png");
    x = 346;
    y = 224;
}

void Mario::draw(sf::RenderWindow &w)
{
    character.setTexture(normal);
    character.setPosition(x, y);
    w.draw(character);
}

void Mario::move(sf::Event ev)
{
    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::A)
            x -= 5;
        if (ev.key.code == sf::Keyboard::D)
            x += 5;
    }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x -= 5;
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x += 5;
}