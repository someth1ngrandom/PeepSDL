#pragma once
#include <cstdint>
#include <ostream>

namespace Peep {

struct Color {
    uint8_t r, g, b, a;
    
    Color();
    Color(int red, int green, int blue, int alpha = 255);

    static Color rgb(int red, int green, int blue);
    static Color rgba(int red, int green, int blue, int alpha);
    static Color hex(uint32_t hex, int alpha = 255);

    static Color darken(const Color &col, float factor);
    static Color lighten(const Color &col, float factor);
    
    friend std::ostream &operator<<(std::ostream &os, const Color &c);
    bool operator==(const Color &other) const;

    static void ValidateChannel(int value, const char* name);
};

}