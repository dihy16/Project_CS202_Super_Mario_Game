#include "map.h"

class MenuObject {
public:
	sf::Sprite sprite;
	sf::Texture texture;
	bool isHidden;
    void hide() {
		isHidden = true;
	}
	void reveal() {
		isHidden = false;
	}
	MenuObject() {isHidden = false;}
	MenuObject(std::string filename, float x, float y);
	void init(std::string filename, float x, float y);
	void draw(sf::RenderWindow& window) const;
	bool isMouseOver(sf::RenderWindow& window) const;
	void updateColorOnHover(sf::RenderWindow& window);
};
