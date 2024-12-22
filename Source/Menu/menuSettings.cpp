#include "menuSettings.h"

void MenuSettings::addObserver(IGameStateObserver *observer)
{
    observers.push_back(observer);
}

void MenuSettings::removeObserver(IGameStateObserver *observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void MenuSettings::notifyObserver(int gameState)
{
    for (const auto &o : observers)
    {
        o->changeState(gameState);
    }
}

MenuSettings::MenuSettings()
{
    for (int i = 0; i <= 10; i++) {
        sf::Texture texture;
        texture.loadFromFile(SOUNDBAR_IMG_PATH + std::to_string(i) + ".png");
        texture.setSmooth(true);
        soundbarTextures.push_back(texture);
    }
    this->addMenuOption(new MenuObject(SOUND_CONTROLS_BG, 0.0f, 0.0f));
    this->addMenuOption(new MenuObject(EXIT_BUTTON, 900.0f, 5.0f, 0.1f, 0.1f));
    this->addMenuOption(new MenuObject(soundbarTextures[0], 5 * BLOCK_WIDTH * 1.f + 45.f, 280.0f, 3.f, 3.f));
    this->addMenuOption(new MenuObject(INC_VOLUME, 660.0f, 283.0f, 1.0f, 1.0f));
    this->addMenuOption(new MenuObject(DEC_VOLUME, 5 * BLOCK_WIDTH * 1.f - 25.f, 283.0f, 1.0f, 1.0f));
    this->addMenuOption(new MenuObject(SAVE_BUTTON, 480, 600.0f, 1.0f, 1.0f));

    initText("MUSIC VOLUME", musicVolumeText, sf::Color::Black, menuFont, 8 * BLOCK_WIDTH / 2 + 1 * BLOCK_WIDTH + 20.f, 220.f);
}

void MenuSettings::handleClicking(sf::RenderWindow &window)
{
    int indexButPressed = this->getButClicked(window);
    switch (indexButPressed)
    {
    case ExitButton:
        updateTextureId();
        updateSoundBarTexture();
        notifyObserver(MenuManager::eMainMenu); 
        break;
    case IncVolumeBut:
        incActiveTextureID();
        updateSoundBarTexture();
        break;
    case DecVolumeBut:
        decActiveTextureID();
        updateSoundBarTexture();
        break;
    case SaveBut:
        MarioGameManager::getInstance()->getMusicManager().setVolume(VOLUME_UNIT * activeTextureID);
        break;
    default:
        break;
    }
}

void MenuSettings::draw(sf::RenderWindow &w)
{
    Menu::draw(w);
    w.draw(musicVolumeText);
}

void MenuSettings::handleHovering(sf::RenderWindow &window)
{
	int i = 1; // Do not handle hovering on background
	for (; i < numOfMenuOptions; ++i)
	{
        if (i == MenuOptionID::SoundBarTexture) continue;
		menuOptions[i]->updateColorOnHover(window);
	}
}

void MenuSettings::updateSoundBarTexture()
{
    menuOptions[SoundBarTexture]->setTexture(soundbarTextures[activeTextureID]);
}

void MenuSettings::updateTextureId()
{
    activeTextureID = MarioGameManager::getInstance()->getMusicManager().getVolume() / (soundbarTextures.size() - 1);
}

void MenuSettings::incActiveTextureID()
{
    if (activeTextureID == 10) {
        return;
    }
    ++activeTextureID;
}

void MenuSettings::decActiveTextureID()
{
    if (activeTextureID == 0) {
        return;
    }
    --activeTextureID;
}
