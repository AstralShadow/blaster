#include "globals.hpp"
#include "core.hpp"
#include <SDL2/SDL_keyboard.h>
#include <cmath>


void jump(Entity* entity)
{
    if(entity->support)
        entity->fall_speed = -entity->mass
                              * entity->jump_factor;
    entity->support = nullptr;
}

void drop_down(Entity* entity)
{
    if(entity->support && !entity->support->solid)
    {
        entity->position.y += 1;
        entity->support = nullptr;
    }
}


void move(Entity* entity, SDL_FPoint* motion)
{
    if(motion->y < 0) jump(entity);
    if(motion->y > 0) drop_down(entity);
    if(motion->x == 0) return;

    auto const motion_x = motion->x * entity->speed;

    if(!entity->support)
    {
        entity->position.x += motion_x;
    }
    else
    {
        auto& platform = *(entity->support);
        auto dx = platform.edge1.x - platform.edge2.x;
        auto dy = platform.edge1.y - platform.edge2.y;
        auto angle = atan2(dy, dx);
        
        entity->position.y -= sin(angle) * motion_x + .1;
        entity->position.x -= cos(angle) * motion_x;

        if(entity->position.x > platform.edge2.x)
            entity->position.y -= 1;
        if(entity->position.x < platform.edge1.x)
            entity->position.y -= 1;
    }
}
