#pragma once

#include <string>
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>
#include <vector>

namespace Peep {

class Audio {
public:
    Audio() = default;
    Audio(std::string audioPath, bool isMus = true);

    ~Audio();

    bool Play(int loops = 0, int volume = -1, int channel = -1);
private:
    std::string path;
    bool isItMusic;

    Mix_Music* mus = nullptr;
    Mix_Chunk* cnk = nullptr;
};

}