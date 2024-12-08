#include "gameManager.h"

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
