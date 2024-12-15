#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "musicManager.h"

using SoundBufferManager = ResourceManager<sf::SoundBuffer>;

class GameManager {
private:
    static const int SOUND_ARRAY_SIZE = 40;
    MusicManager musicManager;
    SoundBufferManager soundBufferManager;
    sf::Sound sounds_arr[SOUND_ARRAY_SIZE];
public:
    GameManager() = default;
    void playSound(const std::string& soundName);
    void playMusic(const std::string& musicName);
    void stopMusic();
    MusicManager& getMusicManager();
    SoundBufferManager& getSoundBufferManager();
};

#endif // GAMEMANAGER_H