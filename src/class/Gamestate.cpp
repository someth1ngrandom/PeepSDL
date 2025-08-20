#include "class/Gamestate.h"
#include <SDL3/SDL.h>

namespace Peep {

Gamestate::Gamestate(std::string_view title, int *width, int *height) : gameWindow(title, width, height, SDL_WINDOW_FULLSCREEN, this->gamepads) {}

}