// WARNING: YOU NEED TO PROVIDE A FONT FILE FOR THIS TO WORK!
// A copy of the Noto Sans font has been provided with this sample.
// Take the font and put it in the same directory as the executable that you built.
// If you don't provide a font, it will throw an error.
#include <iostream>
#include <class/Window.h> // for Peep::Window
#include <class/Color.h> // for Peep::Color
#include <class/Rect.h> // for Peep::Rect
#include <class/Text.h> // for Peep::Text

const std::string kFontPath = "font.ttf"; // define the path to the font as a constant

int main() {
    Peep::Window window("PeepSDL Sample Window", 800, 600);
    window.InitTTF(); // init SDL_ttf for text rendering

    // premake some rectangles and text, remaking them every frame is expensive
    Peep::Rect myRect({
        // this is the transform of this rectangle, basically its position and scale
        150, // X position
        150, // Y position
        120, // width
        120 // height
    }, Peep::Color::white() /* give it a white color */, false /* make it not filled */);

    Peep::Rect myFilledRect({
        340, // X position
        240, // Y position
        120, // width
        60 // height
    }, Peep::Color::hex(0x26ABBF /* a blue color */), true /* this makes it filled */);

    // make a text
    Peep::Text myText({
        // this is the vector2 position for text, text doesnt use a x y width height style format
        400, // X position
        400 // Y position
    }, Peep::Color::white(), 
    "This is some text!", // the content of the text
    kFontPath, // the path to the font to use
    32 // the size of the text in pixels
    );

    // make a big text
    Peep::Text myHugeText({
        150, // X position
        480 // Y position
    }, Peep::Color::white(), "This is a very big text!", kFontPath, 60);

    // make some colored text
    Peep::Text myRedText({
        150, // X position
        270 // Y position
    }, Peep::Color::hex(0xFF0000 /* red color */), "I am red", kFontPath, 32);

    Peep::Text myGreenText({
        150, // X position
        270 + 32 // Y position
    }, Peep::Color::hex(0x00ff00 /* green color */), "I am green", kFontPath, 32);

    Peep::Text myBlueText({
        150, // X position
        270 + 32*2 // Y position
    }, Peep::Color::hex(0x0000FF /* green color */), "I am blue", kFontPath, 32);

    window.SetLogicLoop([](){});   // define an empty logic loop
    window.SetDrawLoop([&myRect, &myFilledRect, &window, &myText, &myHugeText, &myRedText, &myGreenText, &myBlueText /* capture local variables into lambda (important!!) */]() {
        // this is our draw loop, it is where we draw our objects
        myRect.Draw(window); // draw the rect using our window
        myFilledRect.Draw(window);

        myText.Draw(window); // draw the text
        myHugeText.Draw(window);
        
        myRedText.Draw(window);
        myGreenText.Draw(window);
        myBlueText.Draw(window);
    });

    window.BeginLoop(Peep::Color::hex(0x2A2A2A)); // start our empty loops and fill the background with a dark grey color

    TTF_Quit(); // make sure to close ttf!
    SDL_Quit();
    return 0;
}