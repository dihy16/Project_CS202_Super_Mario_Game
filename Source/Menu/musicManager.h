#ifndef MusicManager_H
#define MusicManager_H
#include "resourceManager.h"

template <typename T>
class ResourceManager;

class MusicManager : public ResourceManager<sf::Music>
{
private:
    std::string currentMusic;

public:
    void play(const std::string &musicName);
    void stop();
};

#endif