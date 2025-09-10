#include "class/Window.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace Peep {

bool Window::running = true;

Window::Window(std::string_view title, int fullscreenLevel) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD);

    int w = 640;
    int h = 480;
    SDL_WindowFlags flags = 0;

    if (fullscreenLevel > 0) {
        SDL_DisplayID displayId = SDL_GetPrimaryDisplay();
        const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(displayId);
        if (mode) {
            w = mode->w;
            h = mode->h;
        } else {
            throw std::runtime_error(SDL_GetError());
        }
    }

    if (fullscreenLevel == 0) {
        flags |= SDL_WINDOW_FULLSCREEN;
    } else if (fullscreenLevel == 1) {
        flags |= SDL_WINDOW_BORDERLESS;
    }
 
    window = SDL_CreateWindow(title.data(), w, h, flags);
    if (!window) {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_SetWindowResizable(window, false);

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_SetWindowFullscreen(window, true);
    SDL_SetWindowFullscreenMode(window, NULL); 


    // set vsync
    SDL_SetRenderVSync(renderer, 1);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // enable blending, allows for alpha

    lastPerfCounter = SDL_GetPerformanceCounter();
    perfFreq = SDL_GetPerformanceFrequency();
}

Window::Window(std::string_view title, int width, int height, SDL_WindowFlags flags) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD);

    window = SDL_CreateWindow(title.data(), width, height, flags);
    if (!window) {
        throw std::runtime_error(SDL_GetError());
    }


    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        throw std::runtime_error(SDL_GetError());
    }

    // set vsync
    SDL_SetRenderVSync(renderer, 1);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // enable blending, allows for alpha

    lastPerfCounter = SDL_GetPerformanceCounter();
    perfFreq = SDL_GetPerformanceFrequency();
}

Window::~Window() {
    if (mixInited) {
        Mix_CloseAudio();
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void Window::InitTTF() {
    if (!TTF_Init()) {
        throw std::runtime_error(SDL_GetError());
    }
    ttfInited = true;
}

void Window::InitMix(MIX_InitFlags flags/* = MIX_INIT_OGG*/) {
    if (!Mix_Init(flags)) {
        throw std::runtime_error(SDL_GetError());
    }
    mixInited = true;

    SDL_AudioSpec mySpec;
    SDL_zero(mySpec);
    mySpec.freq = 48000;
    mySpec.format = SDL_AUDIO_S16LE;
    mySpec.channels = 2;

    if (!Mix_OpenAudio(-1, &mySpec)) {
        throw std::runtime_error(SDL_GetError());
    }

    Mix_AllocateChannels(16);
    Mix_VolumeMusic(MIX_MAX_VOLUME);
    Mix_Volume(-1, MIX_MAX_VOLUME);
}

void Window::Clear() { SDL_RenderClear(renderer); }
void Window::Present() { SDL_RenderPresent(renderer); }
void Window::SetDrawColor(Color c) { SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a); }

}