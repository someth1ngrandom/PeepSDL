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
    std::string path;
    int size;
    bool isMiddle = false;
    bool isCentered = false;
    bool isWrapped = false;
    bool dontBother = false;

    int wrapWidth = 200;

    Text(Vector2 trns, Color col, std::string txt, std::string pth, int siz = 32, bool wrp = false, int wrw = 200)
        : transform({ trns.x, trns.y, 0, 0 }), color(col), text(txt), path(pth), size(siz), isWrapped(wrp), wrapWidth(wrw) {};

    ~Text() {
        DestroyTexture();
        lastFont = nullptr;
    }

    void Draw(Window &window);
    void SetMiddle(bool c) { isMiddle = c; }
    void MiddleToArea(const Transform &c, Window &window);
    void SetCentered(bool c) { isCentered = c; }
private:
    ::SDL_Texture* textTexture = nullptr;
    ::std::shared_ptr<::TTF_Font> lastFont = nullptr;

    void GenerateTexture(Window &window);
    void DestroyTexture();
    void SetText(const std::string &text, Window &window);
};

}