#include "class/Color.h"
#include <algorithm>

namespace Peep {

Color::Color() : r(0), g(0), b(0), a(255) {}
Color::Color(int red, int green, int blue, int alpha) : r(red), g(green), b(blue), a(alpha) {}

void Color::ValidateChannel(int value, const char* name) {
    if (value < 0 || value > 255)
        throw std::runtime_error(std::string("Color channel ") + name + " out of range");
}

Color Color::rgb(int red, int green, int blue) {
    ValidateChannel(red  , "red");
    ValidateChannel(green, "green");
    ValidateChannel(blue , "blue");
    return Color(red, green, blue);
}

Color Color::rgba(int red, int green, int blue, int alpha) {
    ValidateChannel(red  , "red");
    ValidateChannel(green, "green");
    ValidateChannel(blue , "blue");
    ValidateChannel(alpha, "alpha");
    return Color(red, green, blue, alpha);
}

Color Color::hex(uint32_t hex, int alpha) {
    return Color(
        (hex >> 16) & 0xFF,
        (hex >> 8) & 0xFF,
        hex & 0xFF,
        alpha
    );
}

Color Color::darken(const Color &col, float factor) {
    factor = std::clamp(factor, 0.0f, 1.0f);

    return Color::rgb(
        std::max(0, static_cast<int>(col.r * factor)),
        std::max(0, static_cast<int>(col.g * factor)),
        std::max(0, static_cast<int>(col.b * factor))
    );
}

Color Color::lighten(const Color &col, float factor) {
    factor = std::clamp(factor, 0.0f, 1.0f);

    return Color::rgb(
        std::min(255, static_cast<int>(col.r + (255 - col.r) * factor)),
        std::min(255, static_cast<int>(col.g + (255 - col.g) * factor)),
        std::min(255, static_cast<int>(col.b + (255 - col.b) * factor))
    );
}

std::ostream& operator<<(std::ostream &os, const Color &c) {
    return os << "Color(" << int(c.r) << ", " << int(c.g) << ", " << int(c.b) << ", " << int(c.a) << ")";
}

bool Color::operator==(const Color &other) const {
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

Color Color::white() { return Color::hex(0xFFFFFF); }
Color Color::black() { return Color::hex(0x000000); }

}