#ifndef MENU_OBJECT_H
#define MENU_OBJECT_H

#include <SFML/Graphics.hpp>

class MenuObject
{
public:
	sf::Sprite sprite;
	sf::Texture texture;
	bool isHidden;
	void hide()
	{
		isHidden = true;
	}
	void reveal()
	{
		isHidden = false;
	}
	MenuObject() { isHidden = false; }
	MenuObject(std::string filename, float x, float y);
	MenuObject(std::string filename, float x, float y, float scaleX, float scaleY);
	MenuObject(const sf::Texture& texture, float x, float y, float scaleX, float scaleY);
	MenuObject(std::string filename, float x, float y, sf::IntRect &r, float scaleX, float scaleY);
	MenuObject(float x, float y, float scaleX, float scaleY);
	void init(std::string filename, float x, float y);
	virtual void draw(sf::RenderWindow &window) const;
	bool isMouseOver(sf::RenderWindow &window) const;
	void updateColorOnHover(sf::RenderWindow &window);
	void updateFromTarget(sf::RenderWindow &window, MenuObject* target);
	void setScale(float scaleX, float scaleY);
	void setTextureRect(const sf::IntRect &r);
	void setTexture(const sf::Texture& texture);
	void setTextureWithTR(const std::string& filename, const sf::IntRect &r); // set texture then set texture rect
	virtual void setString(const std::string& str) {}
	virtual std::string getString() { return std::string(); }
};

#endif