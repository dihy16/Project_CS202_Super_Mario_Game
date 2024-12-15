#include "gameManager.h"

void GameManager::playSound(const std::string& soundName)
{
    // Find index of open slot to allocate new sound 
    int index = 0;
    while (index < SOUND_ARRAY_SIZE) {
        if (sounds_arr[index].getStatus() != sf::Sound::Playing)
            break;
        ++index;
    }
    if (index >= SOUND_ARRAY_SIZE)
        throw std::runtime_error("Sound array overflow");

    sounds_arr[index].setBuffer(*getSoundBufferManager().get(soundName));
    sounds_arr[index].play();

}

void GameManager::playMusic(const std::string& musicName)
{
    musicManager.play(musicName);
}

void GameManager::stopMusic()
{
    musicManager.stop();
}

MusicManager &GameManager::getMusicManager()
{
    return musicManager;
}

SoundBufferManager& GameManager::getSoundBufferManager()
{
    return soundBufferManager;
}
