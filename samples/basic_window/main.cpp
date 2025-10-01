#include <iostream>
#include <class/Window.h> // for Peep::Window
#include <class/Color.h> // for Peep::Color

int main() {

    Peep::Window window("PeepSDL Sample Window", 800, 600); // create an 800x600 SDL window
    // for fullscreen, you can do this:
    // Peep::Window window("PeepSDL Sample Window", 1 /* <-- change this to 2 for borderless */);

    window.SetLogicLoop([](){});   // define an empty logic and draw loop,
    window.SetDrawLoop([](){});    // we are not doing anything yet in this sample

    window.BeginLoop(Peep::Color::hex(0x2A2A2A)); // start our empty loops and fill the background with a dark grey color

    SDL_Quit(); // quit manually because we can't trust the stack to do it for us
    return 0;
}