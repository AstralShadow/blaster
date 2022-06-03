#ifndef INCLUDE_DATA_HPP
#define INCLUDE_DATA_HPP

#include <cstdint>
#include <vector>
#include <SDL_rect.h>

using std::vector;

struct Platform
{
    SDL_FPoint edge1, edge2;
    bool can_drop = true;
    bool rotating = false;
};

struct Wall
{
    SDL_FPoint edge1, edge2;
};

struct Entity
{
    float mass = 4;
    float max_speed = 6;
    float jump_power = 5;
    float acceleration = 2;

    SDL_FRect position;
    SDL_FPoint velocity {0, 0};
    Platform* foothold = nullptr;
};


struct Data
{
    vector<Platform> platforms;
    vector<Wall> walls;

    vector<Entity> entities;
    vector<SDL_Point> loot;

    int score = 0;
};

#endif // INCLUDE_DATA_HPP
