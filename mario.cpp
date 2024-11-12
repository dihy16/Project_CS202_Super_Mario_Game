#include "mario.h"

Mario::Mario()
{
    normal.loadFromFile("Images/marionormal.png");
}

void Mario::draw(sf::RenderWindow& w)
{
    character.setTexture(normal);
}

void Mario::move(sf::Event ev)
{
    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::A) x -= 2;
        else if (ev.key.code == sf::Keyboard::D) x += 2;
    }
}