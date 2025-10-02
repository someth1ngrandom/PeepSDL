#include <iostream>
#include <class/Window.h>
#include <class/Color.h>
#include <class/Rect.h>
#include <class/Random.h>

int main() {
    Peep::Window window("PeepSDL Testing", 640, 360);
    Peep::Random rng;

    window.SetLogicLoop([](){});
    window.SetDrawLoop([&window, &rng]() {
        Peep::Rect({ 100, 100, 100, 100 }, Peep::Color::white(), true).Draw(window, 1, -1, std::make_optional<Peep::Transform>({
            rng.NextFloat(0, 100),
            rng.NextFloat(0, 100),
            rng.NextFloat(0, 100),
            rng.NextFloat(0, 100)
        }));
    });

    window.BeginLoop(Peep::Color::black());

    SDL_Quit();
    return 0;
}