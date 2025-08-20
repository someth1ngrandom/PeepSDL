#pragma once

#include "class/Color.h"
#include "class/Transform.h"

class SDL_Texture;

namespace Peep {

class Window;

class Texture {
public:
    Transform transform;
    std::string path;

    Texture(Transform trns, std::string pth)
        : transform(trns), path(pth) {};

    ~Texture() {
        DestroyTexture();
    }

    void Draw(Window &window);
private:
    ::SDL_Texture* texture = nullptr;

    void GenerateTexture(Window &window);
    void DestroyTexture();
};

}