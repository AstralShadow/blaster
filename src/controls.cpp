#include "globals.hpp"
#include "core.hpp"
#include <SDL2/SDL_keyboard.h>
#include <cmath>


void jump(Entity& entity)
{
    if(entity.foothold)
    {
        entity.fall_speed = -1 * entity.jump_power;
    }
    entity.foothold = nullptr;
}

void drop_down(Entity& entity)
{
    if(entity.foothold && entity.foothold->can_drop)
    {
        entity.position.y += 1;
        entity.foothold = nullptr;
    }
}


void move(Entity& entity, SDL_FPoint const& direction)
{
    if(direction.y < 0) jump(entity);
    if(direction.y > 0) drop_down(entity);
    if(direction.x == 0) return;

    auto const motion_x = direction.x * entity.speed;

    if(entity.foothold){
        auto& platform = *(entity.foothold);
        auto dx = platform.edge1.x - platform.edge2.x;
        auto dy = platform.edge1.y - platform.edge2.y;
        auto angle = atan2(dy, dx);
        
        entity.position.y -= sin(angle) * motion_x + .1;
        entity.position.x -= cos(angle) * motion_x;

        if(entity.position.x > platform.edge2.x)
            entity.position.y -= 1;
        if(entity.position.x < platform.edge1.x)
            entity.position.y -= 1;
    }
    else
    {
        entity.position.x += motion_x;
    }
}
