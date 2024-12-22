#ifndef MusicManager_H
#define MusicManager_H
#include "resourceManager.h"

template <typename T>
class ResourceManager;

class MusicManager : public ResourceManager<sf::Music>
{
private:
    std::string currentMusic;
    int volume;
public:
    void play(const std::string &musicName);
    void stop();
    void setVolume(int volume);
    int getVolume();
};

#endif