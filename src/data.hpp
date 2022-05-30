#ifndef INCLUDE_DATA_HPP
#define INCLUDE_DATA_HPP

#include <cstdint>
#include <vector>
#include <SDL_rect.h>

using std::vector;


struct Platform
{
    SDL_FPoint edge1, edge2;
    bool stable = true;
    bool solid = false;
};

struct Wall
{
    SDL_FPoint edge1, edge2;
};

struct Entity
{
    SDL_FRect position;
    float speed = 6;
    float jump_state = -1;
    float mass = 4;
    float jump_factor = 1.2;
    Platform* support = nullptr;

    float fall_speed = 0;
    //float movement_speed = 0;
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
