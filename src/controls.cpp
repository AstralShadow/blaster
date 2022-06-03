#include "globals.hpp"
#include "core.hpp"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_timer.h>
#include <cmath>


void jump(Entity& entity)
{
    auto const max_latency = 100;
    auto const now = SDL_GetTicks();
    auto const& drop_tick = entity.drop_tick;

    if(entity.foothold || now - drop_tick < max_latency)
    {
        entity.velocity.y = -1 * entity.jump_power;
    }

    entity.foothold = nullptr;
    entity.drop_tick = SDL_GetTicks() - max_latency;
}

void drop_down(Entity& entity)
{
    if(entity.foothold && entity.foothold->can_drop)
    {
        entity.position.y += 1;
        entity.foothold = nullptr;
        entity.drop_tick = SDL_GetTicks();
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
        auto& e1 = entity.foothold->edge1;
        auto& e2 = entity.foothold->edge2;

        auto dx = e2.x - e1.x;
        auto dy = e2.y - e1.y;
        auto angle = std::atan2(dy, dx);

        auto& pos = entity.position;
        float edge_dist;
        if(motion > 0)
        {
            auto dx2 = pos.x + pos.w / 2 - e2.x;
            auto dy2 = pos.y + pos.h - e2.y;
            edge_dist = std::hypot(dx2, dy2);
        }
        else
        {
            auto dx1 = pos.x + pos.w / 2 - e1.x;
            auto dy1 = pos.y + pos.h - e1.y;
            edge_dist = std::hypot(dx1, dy1);
        }


        auto pull = entity.mass * sin(angle) * g_gravity;
        motion += pull;
        if(std::abs(motion) > edge_dist)
        {
            auto full_motion = motion;
            motion = edge_dist *
                      (std::signbit(motion) ? -1 : 1);
            entity.position.x += full_motion - motion;
            drop_down(entity);
        }

        entity.position.y += sin(angle) * motion - .1;
        entity.position.x += cos(angle) * motion;


        /* Move the player up when he falls of an edge
         * so he will be over any platforms that share
         * the same edge. */
        if(entity.position.x > e2.x)
            entity.position.y -= 1;
        if(entity.position.x < e1.x)
            entity.position.y -= 1;
    }
    else
    {
        entity.position.x += motion;
    }
}
