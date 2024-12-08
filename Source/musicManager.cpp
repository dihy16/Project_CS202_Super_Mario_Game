#include "musicManager.h"

void MusicManager::play(const std::string &musicName)
{
    if (musicName != "")
		this->currentMusic = musicName;
	if (!this->currentMusic.empty())
		m_resources[this->currentMusic]->play();
}