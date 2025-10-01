#include "class/Text.h"
#include "class/Window.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Exceptions.h"
#include "class/Color.h"
#include "class/Transform.h"

namespace Peep {

Text::Text(Vector2 trns, Color col, std::string txt, std::string pth, int siz, bool wrp, int wrw)
        : transform({ trns.x, trns.y, 0, 0 }), color(col), text(txt), path(pth), size(siz), isWrapped(wrp), wrapWidth(wrw)
{
    lastFont = ::TTF_OpenFont(path.c_str(), size);
    if (!lastFont) {
        throw FontCreationException(SDL_GetError());
    }
}

void Text::DestroyTexture() {
    if (textTexture) {
        ::SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
}

void Text::GenerateTexture(Window &window) {
    if (text == "") dontBother = true;
    if (dontBother) return;

    DestroyTexture(); // destroy old texture

    // make the texture
    SDL_Surface* surface;
    if (isWrapped) {
        surface = TTF_RenderText_Blended_Wrapped(lastFont, text.c_str(), 0, { color.r, color.g, color.b, color.a }, wrapWidth);
    } else {
        surface = TTF_RenderText_Blended(lastFont, text.c_str(), 0, { color.r, color.g, color.b, color.a });
    }
    if (!surface) {
        throw std::runtime_error(SDL_GetError());
    }

    // before we free, copy surfaces width and height
    transform.SetScaleW(static_cast<float>(surface->w));
    transform.SetScaleH(static_cast<float>(surface->h));

    // convert this surface to texture
    textTexture = SDL_CreateTextureFromSurface(window.GetRenderer(), surface);
    SDL_DestroySurface(surface);
    if (!textTexture) {
        throw std::runtime_error(SDL_GetError());
    }
}

void Text::SetText(const std::string &text, Window &window) {
    if (this->text != text) {
        this->text = text;
        GenerateTexture(window);
    }
}

void Text::MiddleToArea(const Transform &c, Window &window) {
    GenerateTexture(window);

    const float textW = transform.GetScl().w;
    const float textH = transform.GetScl().h;

    const float areaX = c.GetPos().x;
    const float areaY = c.GetPos().y;
    const float areaW = c.GetScl().w;
    const float areaH = c.GetScl().h;

    transform.SetPosition({
        areaX + (areaW - textW) / 2.0f,
        areaY + (areaH - textH) / 2.0f
    });
}

void Text::Draw(Window &window) {
    if (dontBother) return;
    if (!textTexture) {
        GenerateTexture(window);
    }

    const float textW = transform.GetScl().w;
    const float textH = transform.GetScl().h;
    SDL_FRect drawRect;

    if (isMiddle) {
        drawRect = {
            (window.GetWindowSize().w - textW) / 2.0f,
            (window.GetWindowSize().h - textH) / 2.0f,
            textW,
            textH
        };
    } else if (isCentered) {
        drawRect = {
            (window.GetWindowSize().w - textW) / 2.0f,
            transform.GetPos().y,
            textW,
            textH
        };
    } else {
        drawRect = transform.GetRect();
    }

    SDL_RenderTexture(window.GetRenderer(), textTexture, nullptr, &drawRect);
}

Text::~Text() {
    DestroyTexture();
    if (lastFont && TTF_WasInit() > 0) {
        TTF_CloseFont(lastFont);
        lastFont = nullptr;
    }
}

}