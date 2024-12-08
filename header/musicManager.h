#pragma once

#include "resourceManager.h"

class MusicManager : public ResourceManager<sf::Music> {
private:
    string currentMusic;
public:
    void play(const string& musicName);
    void stop();
};