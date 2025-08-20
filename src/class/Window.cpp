#include "class/Window.h"
#include <format>
#include "class/Gamestate.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace Peep {

bool Window::running = true;

Window::Window(std::string_view title, int *width, int *height, SDL_WindowFlags flags, GamepadMap &gamepads) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD);

    int realWidth = 1600;
    int realHeight = 900;

    SDL_DisplayID displayId = SDL_GetPrimaryDisplay();
    const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(displayId);
    if (mode) {
        realWidth = mode->w;
        realHeight = mode->h;
    } else {
        // we fall back to the default resolution
    }

    if (width) *width = realWidth;
    if (height) *height = realHeight;

    window = SDL_CreateWindow(title.data(), realWidth, realHeight, flags);
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

Window::~Window() {/* smart ptrs do this automatically, unlike retarded ptrs
    if (textFont) {
        printf("Ambatuclose %p\n", textFont);
        TTF_CloseFont(textFont);
        textFont = nullptr;
    }
    if (textFontHuge) {
        TTF_CloseFont(textFontHuge);
        textFontHuge = nullptr;
    }*/
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

void Window::InitTTF(std::string_view fontPath) {
    if (!TTF_Init()) {
        throw std::runtime_error(SDL_GetError());
    }
    ttfInited = true;

    //textFont = TTF_OpenFont("assets/fonts/Main.ttf", 32); // hardcoded font because fuck you, thats why
    textFont = ::std::shared_ptr<::TTF_Font>(
        TTF_OpenFont(fontPath.data(), 32),
        [](::TTF_Font* f) {
            if (f) ::TTF_CloseFont(f);
        }
    );
    textFontHuge = ::std::shared_ptr<::TTF_Font>(
        TTF_OpenFont(fontPath.data(), 128),
        [](::TTF_Font* f) {
            if (f) ::TTF_CloseFont(f);
        }
    );

    if (!textFont || !textFontHuge) {
        throw std::runtime_error(SDL_GetError());
    }
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

int Window::GetJoystickCount(Gamestate &state) const noexcept { return state.gamepads.size(); }
void Window::Clear() { SDL_RenderClear(renderer); }
void Window::Present() { SDL_RenderPresent(renderer); }
void Window::SetDrawColor(Color c) { SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a); }

}