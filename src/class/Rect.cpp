#include "class/Rect.h"
#include "class/Window.h"
#include "class/Transform.h"
#include <SDL3/SDL.h>

namespace Peep {

std::ostream &operator<<(std::ostream &os, const Rect &r) {
    return os << "Rect {" << std::endl <<
        "\ttransform: " << r.transform << std::endl <<
        "\tcolor: " << r.color << std::endl <<
        "\tfilled: " << r.filled << std::endl <<
    "}";
}

void Rect::Draw(Window &window, int outlineThickness, int strokeThickness) const {
    if (filled) {
        window.SetDrawColor(color);
        SDL_RenderFillRect(window.GetRenderer(), &transform.GetRect());
    }
    
    if (strokeThickness > 0) {
        SDL_FRect r = {
            transform.GetPos().x - strokeThickness,
            transform.GetPos().y - strokeThickness,
            transform.GetScl().w + strokeThickness * 2,
            transform.GetScl().h + strokeThickness * 2
        };
        
        // draw stroke
        window.SetDrawColor(Color::lighten(color, 0.3));
        SDL_RenderFillRect(window.GetRenderer(), &r);

        window.SetDrawColor(color);
        SDL_RenderFillRect(window.GetRenderer(), &transform.GetRect());
    } else if (!filled) {
        for (int i = 0; i < outlineThickness; ++i) {
            SDL_FRect r = {
                transform.GetPos().x - i,
                transform.GetPos().y - i,
                transform.GetScl().w + i * 2,
                transform.GetScl().h + i * 2
            };

            window.SetDrawColor(color);
            SDL_RenderRect(window.GetRenderer(), &r);
        }
    }
}

float Rect::GetMiddleX(const Scale &windowScale) const {
    return (windowScale.w - transform.GetScl().w) / 2.0f;
}

float Rect::GetMiddleY(const Scale &windowScale) const {
    return (windowScale.h - transform.GetScl().h) / 2.0f;
}

bool Rect::IsCollidingWithTransform(const Transform &other) const {
    return (transform.GetPos().x < other.GetPos().x       + other.GetScl().w) &&
           (transform.GetPos().x + transform.GetScl().w   > other.GetPos().x) &&
           (transform.GetPos().y < other.GetPos().y       + other.GetScl().h) &&
           (transform.GetPos().y + transform.GetScl().h   > other.GetPos().y);
}

}