#pragma once
#include <SFML/Graphics.hpp>
class Mario
{
private:
   int state = 0, x, y;
   bool live = true;
   sf::Sprite character;
   sf::Texture normal, super, fiery, invincible;
public:
   Mario();
   void draw(sf::RenderWindow &window);
   void move(sf::Event ev);
};