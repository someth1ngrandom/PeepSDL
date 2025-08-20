#include "class/Audio.h"
#include <vector>
#include <algorithm>

namespace Peep {

Audio::Audio(std::string audioPath, bool isMus)
        : path(audioPath), isItMusic(isMus)
{
    // create a chunk/music
    if (isItMusic) {
        mus = Mix_LoadMUS(path.c_str());
        if (!mus) {
            throw std::runtime_error(SDL_GetError());
        }
    } else {
        cnk = Mix_LoadWAV(path.c_str());
        if (!cnk) {
            throw std::runtime_error(SDL_GetError());
        }
    }
}

Audio::~Audio() {
    if (isItMusic && mus) {
        if (Mix_PlayingMusic()) {
            Mix_HaltMusic();
        }
        Mix_FreeMusic(mus);

        mus = nullptr;
    }

    if (!isItMusic && cnk) {
        Mix_FreeChunk(cnk);
        cnk = nullptr;
    }
}

bool Audio::Play(int loops, int volume, int channel) {
    if (volume >= 0) {
        if (isItMusic) Mix_VolumeMusic(std::clamp(volume, 0, 128));
        else Mix_Volume(-1, std::clamp(volume, -1, 128));
    }
    if (isItMusic) {
        return Mix_PlayMusic(mus, loops);
    } else  {
        return Mix_PlayChannel(channel, cnk, loops);
    }
}

}