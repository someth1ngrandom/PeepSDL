#pragma once

#include "class/Window.h"
#include <vector>
#include "class/Audio.h"
#include <unordered_map>
#include <string>

namespace Peep {

struct SDL_Gamepad;

struct Gamestate {
    GamepadMap gamepads;

    Window gameWindow;

    Audio* CreateAudio(const std::string &path, bool isMus = false);

    Gamestate(std::string_view title, int *width = nullptr, int *height = nullptr);
};

}