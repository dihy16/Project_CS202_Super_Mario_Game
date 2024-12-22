#include "musicManager.h"

void MusicManager::play(const std::string &musicName)
{
    if (musicName != "")
		this->currentMusic = musicName;
	if (!this->currentMusic.empty())
		if (m_resources[this->currentMusic]->getStatus() != sf::Music::Playing)
			m_resources[this->currentMusic]->play();
}

void MusicManager::stop()
{
	for (auto music : m_resources) {
		music.second->stop();
	}
	this->currentMusic.clear();
}
