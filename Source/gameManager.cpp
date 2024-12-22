#include "gameManager.h"

void GameManager::inputSounds()
{
    for (auto& soundName : vSoundName) {
        getSoundBufferManager().loadFromFile(soundName, std::string("resource/Sound/") + soundName + ".wav");
    }
    initSoundMap();
}

void GameManager::inputMusic()
{
    for (auto& musicName : vMusicName) {
        getMusicManager().loadFromFile(musicName, std::string("resource/Music/") + musicName + ".ogg");
    }
    initMusicMap();
    getMusicManager().setVolume(DEFAULT_VOLUME);
}

void GameManager::initSoundMap() {
    for (size_t i = 0; i < vSoundName.size(); ++i) {
        soundMap[static_cast<SoundName>(i)] = vSoundName[i];
    }
}

void GameManager::initMusicMap() {
    for (size_t i = 0; i < vMusicName.size(); ++i) {
        musicMap[static_cast<MusicName>(i)] = vMusicName[i];
    }
}

GameManager::GameManager()
{
    inputSounds();
    inputMusic();
}

void GameManager::playSound(SoundName soundName)
{
    const std::string str_soundName = soundMap[soundName];
    // Find index of open slot to allocate new sound 
    int index = 0;
    while (index < SOUND_ARRAY_SIZE) {
        if (sounds_arr[index].getBuffer() == getSoundBufferManager().get(str_soundName) && sounds_arr[index].getStatus() == sf::Sound::Playing) {
            return; // sound already playing
        }
        if (sounds_arr[index].getStatus() != sf::Sound::Playing)
            break;
        ++index;
    }
    if (index >= SOUND_ARRAY_SIZE)
        throw std::runtime_error("Sound array overflow");

    sounds_arr[index].setBuffer(*getSoundBufferManager().get(str_soundName));
    sounds_arr[index].play();

}

void GameManager::playMusic(MusicName musicName)
{
    const std::string str_musicName = musicMap[musicName];
    musicManager.play(str_musicName);
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
