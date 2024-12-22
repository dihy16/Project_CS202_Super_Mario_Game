#ifndef MENUSETTINGS_H
#define MENUSETTINGS_H
#include "../definition.h"
#include "menu.h"
#include "menuObserver.h"
#include "marioGameManager.h"

class MarioGameManager;
class MenuManager;

class MenuSettings : public Menu
{
private:
	std::vector<IGameStateObserver *> observers; // List of observers
	std::vector<sf::Texture> soundbarTextures;
	sf::Text musicVolumeText;
	int activeTextureID;
	enum MenuOptionID {
		BG,
		ExitButton,
		SoundBarTexture,
		IncVolumeBut,
		DecVolumeBut,
		SaveBut
	};
public:
	bool isHidden;
	void addObserver(IGameStateObserver *observer);
	void removeObserver(IGameStateObserver *observer);
	void notifyObserver(int gameState);
	MenuSettings();
	void handleClicking(sf::RenderWindow &window);
	void draw(sf::RenderWindow &w) override;
	void handleHovering(sf::RenderWindow &window);
	void updateSoundBarTexture();
	void updateTextureId();
	void incActiveTextureID();
	void decActiveTextureID();
};

#endif