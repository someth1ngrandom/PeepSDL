#pragma once

#include <random>

namespace Peep {

class Random
{
public:
    Random()
        : engine(std::random_device{}()) {};

    int NextInt(int min, int max);
    float NextFloat(float min, float max);
    bool Coinflip();

private:
    std::mt19937 engine;
};

}