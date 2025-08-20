#pragma once

#include "class/Color.h"
#include "class/Transform.h"
#include <memory>

class TTF_Font;

namespace Peep {

class Window;
class SDL_Texture;

class Text {
public:
    Transform transform;
    Color color;
    std::string text;
    bool isMiddle = false;
    bool isCentered = false;
    bool isWrapped = false;
    bool isHuge = false;
    bool dontBother = false;

    int wrapWidth = 200;

    Text(Transform trns, Color col, std::string txt, bool huge = false, bool wrp = false, int wrw = 200)
        : transform(trns), color(col), text(txt), isHuge(huge), isWrapped(wrp), wrapWidth(wrw) {};

    ~Text() {
        DestroyTexture();
        lastFont = nullptr;
    }

    void Draw(Window &window);
    void SetMiddle(bool c) { isMiddle = c; }
    void MiddleToArea(const Transform &c, Window &window);
    void SetCentered(bool c) { isCentered = c; }
private:
    ::SDL_Texture* textTexture;
    ::std::shared_ptr<::TTF_Font> lastFont;

    void GenerateTexture(Window &window);
    void DestroyTexture();
    void SetText(const std::string &text, Window &window);
};

}