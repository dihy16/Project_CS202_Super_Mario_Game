#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "musicManager.h"
//using SoundManager = ResourceManager<sf::SoundBuffer>;

class GameManager {
private:
    //SoundManager soundManager;
    MusicManager musicManager;
public:
    GameManager() = default;
    void playMusic(const string& musicName);
    MusicManager& getMusicManager();
};

#endif // GAMEMANAGER_H