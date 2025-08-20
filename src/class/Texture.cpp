#include "class/Texture.h"
#include "class/Window.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL_image.h>

namespace Peep {

void Texture::DestroyTexture() {
    if (texture) {
        ::SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Texture::GenerateTexture(Window &window) {
    DestroyTexture(); // destroy old texture

    // actually make the texture
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        throw std::runtime_error(SDL_GetError());
    }

    // before we free, copy surfaces width and height
    /*transform.SetScaleW(static_cast<float>(surface->w));
    transform.SetScaleH(static_cast<float>(surface->h));*/

    // convert this surface to texture
    texture = SDL_CreateTextureFromSurface(window.GetRenderer(), surface);
    SDL_DestroySurface(surface);
    if (!texture) {
        throw std::runtime_error(SDL_GetError());
    }
}

void Texture::Draw(Window &window) {
    if (!texture) {
        GenerateTexture(window);
        if (!texture) return;
    }

    const SDL_FRect& dst = transform.GetRect();
    SDL_RenderTexture(window.GetRenderer(), texture, nullptr, &dst);
}

}