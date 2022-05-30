#include "random.hpp"
#include <random>

static std::random_device rd_dev;
static std::mt19937 generator(rd_dev());


int random(int min, int max)
{
    std::uniform_int_distribution dist(min, max);
    return dist(generator);
}

float randomf(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(generator);
}
