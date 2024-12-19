#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "musicManager.h"
#include <map>

using SoundBufferManager = ResourceManager<sf::SoundBuffer>;

class GameManager
{
private:
    static const int SOUND_ARRAY_SIZE = 40;
    MusicManager musicManager;
    SoundBufferManager soundBufferManager;
    sf::Sound sounds_arr[SOUND_ARRAY_SIZE];
    std::vector<std::string> vSoundName = {"breakblock", "bump", "coin", "fireball", "jump_super", "kick", "stomp", "powerup_appears",
                                           "powerup", "pipe", "flagpole", "bowser_falls", "bowser_fire", "mario_die", "stage_clear",
                                           "game_over", "1-up", "warning", "world_clear", "pause", "beep", "fireworks"};
    std::vector<std::string> vMusicName = {"bowsercastle", "invincibility", "overworld", "underwater", "underworld"};
    void inputSounds();
    void inputMusic();

protected:
    void initSoundMap();
    void initMusicMap();

public:
    enum SoundName
    {
        breakblock,
        bump,
        coin,
        fireball,
        jump,
        kick,
        stomp,
        powerup_appears,
        powerup,
        pipe,
        flagpole,
        bowser_falls,
        bowser_fire,
        mario_die,
        stage_clear,
        game_over,
        add_coin,
        warning,
        world_clear,
        pause,
        beep,
        fireworks,
    };
    enum MusicName
    {
        bowsercastle,
        invincibility,
        overworld,
        underwater,
        underworld,
    };
    std::map<SoundName, std::string> soundMap;
    std::map<MusicName, std::string> musicMap;
    GameManager();
    void playSound(SoundName soundName);
    void playMusic(MusicName musicName);
    void stopMusic();
    MusicManager &getMusicManager();
    SoundBufferManager &getSoundBufferManager();
};

#endif // GAMEMANAGER_H