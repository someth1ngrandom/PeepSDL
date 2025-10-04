#pragma once

#include "class/Color.h"
#include <SDL3/SDL.h>
#include <functional>
#include <string>
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "class/Text.h"
#include "class/Transform.h"
#include <cassert>
#include <vector>
#include <optional>
#include <stdexcept>
#include "Exceptions.h"

namespace Peep {

struct Gamestate;

class Window
{
public:
    explicit Window(std::string_view title, int fullscreenLevel = 0);
    explicit Window(std::string_view title, int width, int height, SDL_WindowFlags flags = 0);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void Clear();
    void Present();
    void SetDrawColor(Color c);

    void InitTTF();
    void InitMix(MIX_InitFlags flags = MIX_INIT_OGG);

    void GracefulClose() { running = false; };

    void SetLogicLoop(std::function<void()> cb) {
        logicLoop = cb;
    }

    void SetDrawLoop(std::function<void()> cb) {
        drawLoop = cb;
    }

    void BeginLoop(Color bgColor) {
        assert(logicLoop && "Logic loop not set, are you stupid?");
        assert(drawLoop && "Logic loop not set, are you stupid?");

        static double fpsReportTimer = 0.0;

        while (running) {
            uint64_t frameStart = SDL_GetPerformanceCounter();

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    GracefulClose();
                } else if (event.type == SDL_EVENT_KEY_DOWN) {
                    try {
                        if (keyCallback) keyCallback(event.key.key);
                    } catch (const std::exception &e) {
                        throw KeyCallbackException(e.what());
                    }
                } else if (event.type == SDL_EVENT_KEY_UP) {
                    try {
                        if (keyUpCallback) keyUpCallback(event.key.key);
                    } catch (const std::exception &e) {
                        throw KeyCallbackException(e.what());
                    }
                }

                try {
                    if (eventCallback) eventCallback(event);
                } catch (const std::exception &e) {
                    throw EventCallbackException(e.what());
                }
            }

            deltaTime = double(frameStart - lastPerfCounter) / perfFreq;
            lastPerfCounter = frameStart;
            if (deltaTime > 0) fps = 1.0f / float(deltaTime);

            // do our logic loop first
            if (logicStarted) {
                try {
                    logicLoop();
                } catch (const std::exception &e) {
                    throw LogicLoopException(e.what());
                }
            }

            SetDrawColor(bgColor);
            Clear();

            // then our drawing
            try {
                drawLoop();
            } catch (const std::exception &e) {
                throw DrawLoopException(e.what());
            }

            Present();

            uint64_t frameEnd = SDL_GetPerformanceCounter();
            double frameDuration = (frameEnd - frameStart) / perfFreq;

            fpsReportTimer += deltaTime;
            if (fpsReportTimer >= 0.5) {
                //std::cout << "FPS: " << fps << "\r" << std::flush;

                displayFps = fps;
                fpsReportTimer = 0.0;
            }
        }
    }

    void SetKeyCallback(std::function<void(SDL_Keycode)> cb) {
        keyCallback = cb;
    }

    void SetKeyUpCallback(std::function<void(SDL_Keycode)> cb) {
        keyUpCallback = cb;
    }

    void SetEventCallback(std::function<void(SDL_Event)> cb) {
        eventCallback = cb;
    }

    static void SetRunning(bool r) {
        running = r;
    }

    double GetDeltaTime() const noexcept { return deltaTime; };
    float GetFramesPerSecond() const noexcept { return displayFps; };

    bool GetTTFInitStatus() const noexcept { return ttfInited; }; 
    bool GetMixInitStatus() const noexcept { return mixInited; }; 
    
    void TriggerLoadError();
    
    SDL_Event GetEvent() const noexcept { return event; }
    SDL_Renderer* GetRenderer() const noexcept { return renderer; }

    int GetJoystickCount(Gamestate &state) const noexcept;

    Scale GetWindowSize() const noexcept {
        int w = 0;
        int h = 0;

        SDL_GetWindowSizeInPixels(window, &w, &h);

        return Scale(w, h);
    }
    
    bool logicStarted = false;
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    uint64_t lastPerfCounter;
    uint64_t perfFreq;
    double deltaTime = 0.0;
    float fps = 0.0f;
    float displayFps = 0.f;

    std::vector<::SDL_Gamepad*> gamepads;
    int joystickCount;

    std::function<void(::SDL_Keycode)> keyCallback;
    std::function<void(::SDL_Keycode)> keyUpCallback;
    std::function<void(::SDL_Event)> eventCallback;
    std::function<void()> logicLoop;
    std::function<void()> drawLoop;

    bool ttfInited = false;
    bool mixInited = false;

    const double targetFrameTime = 1.0 / 60.0;

    static bool running;
};

}