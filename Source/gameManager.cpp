#include "../header/gameManager.h"

void GameManager::playMusic(const string& musicName)
{
    musicManager.play(musicName);
}

MusicManager &GameManager::getMusicManager()
{
    return musicManager;
}
