#pragma once

#include "resourceManager.h"

class MusicManager : public ResourceManager<sf::Music> {
private:
    std::string currentMusic;
public:
    void play(const std::string& musicName);
    void stop();
};