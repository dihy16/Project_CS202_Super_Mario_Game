#include "gameManager.h"

void GameManager::playMusic(const std::string& musicName)
{
    musicManager.play(musicName);
}

MusicManager &GameManager::getMusicManager()
{
    return musicManager;
}
