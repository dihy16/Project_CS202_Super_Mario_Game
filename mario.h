#pragma once
#include <SFML/Graphics.hpp>
class Mario
{
private:
   int state = 0, x, y;
   bool live = true;
   sf::Sprite character;
   sf::Texture normal, super, fiery, inviincible;

public:
   Mario();
   void draw(sf::RenderWindow &window);
};