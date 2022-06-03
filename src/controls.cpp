#include "globals.hpp"
#include "core.hpp"
#include <SDL2/SDL_keyboard.h>
#include <cmath>


void jump(Entity& entity)
{
    if(entity.foothold)
    {
        entity.velocity.y = -1 * entity.jump_power;
    }
    entity.foothold = nullptr;
}

void drop_down(Entity& entity)
{
    if(entity.foothold && entity.foothold->can_drop)
    {
        // TODO replace with 1 + distance to foothold 
        entity.position.y += 1;
        entity.foothold = nullptr;
    }
}

void apply_friction(Entity& entity)
{
    auto const acceleration = entity.acceleration;
    auto& speed = entity.velocity.x;

    if(std::abs(speed) < acceleration)
        speed = 0;

    if(speed > 0)
        speed -= acceleration;

    if(speed < 0)
        speed += acceleration;
}

void accelerate(Entity& entity, float const& direction)
{
    auto const max_speed = entity.max_speed;
    auto const acceleration = entity.acceleration;
    auto& speed = entity.velocity.x;
    auto sign = std::signbit(direction) ? -1 : 1;

    if(std::abs(speed) <= max_speed)
    {
        speed += acceleration * sign;
        if(std::abs(speed) > max_speed)
            speed = max_speed * sign;
    }

    if(std::abs(speed) > max_speed)
        apply_friction(entity);
}


void move(Entity& entity, SDL_FPoint const& direction)
{
    if(direction.y < 0) jump(entity);
    if(direction.y > 0) drop_down(entity);

    if(direction.x == 0)
        apply_friction(entity);
    else
        accelerate(entity, direction.x);


    auto motion = entity.velocity.x;

    if(entity.foothold){
        auto& platform = *(entity.foothold);
        auto dx = platform.edge2.x - platform.edge1.x;
        auto dy = platform.edge2.y - platform.edge1.y;
        auto angle = atan2(dy, dx);

        motion += entity.mass * sin(angle) * g_gravity;

        auto motion_y = sin(angle) * motion;
        
        entity.position.y += motion_y - .1;
        entity.position.x += cos(angle) * motion;


        /* Move the player up when he falls of an edge
         * so he will be over any platforms that share
         * the same edge. */
        if(entity.position.x > platform.edge2.x)
            entity.position.y -= 1;
        if(entity.position.x < platform.edge1.x)
            entity.position.y -= 1;
    }
    else
    {
        entity.position.x += motion;
    }
}
