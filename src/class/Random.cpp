#include "class/Random.h"

namespace Peep {

int Random::NextInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}

float Random::NextFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(engine);
}

bool Random::Coinflip() {
    std::uniform_int_distribution<int> dist(0, 1);
    return static_cast<bool>(dist(engine));
}

}