#pragma once
#include "class/Color.h"
#include "class/Transform.h"
#include <optional>

namespace Peep {

class Window;

class Rect
{
public:
    Transform transform;
    Color color;
    bool filled;

    Rect() = default;
    Rect(Transform trns, Color col, bool fil = false)
        : transform(trns), color(col), filled(fil) {};

    void Draw(Window &window, int outlineThickness = 1, int strokeThickness = -1, std::optional<Transform> offset = std::nullopt) const;
    bool IsCollidingWithTransform(const Transform &other) const;

    float GetMiddleX(const Scale &windowScale) const;
    float GetMiddleY(const Scale &windowScale) const;

    bool operator==(const Rect &other) const {
        return transform == other.transform &&
               color == other.color &&
               filled == other.filled;
    }

    friend std::ostream &operator<<(std::ostream &os, const Rect &r);
};

}
