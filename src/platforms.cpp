#include "globals.hpp"
#include "core.hpp"
#include <cmath>


void apply_gravity()
{
    for(auto& entity : g_data.entities)
    {
        auto const& pos = entity.position;
        auto p_middle = pos.x + pos.w / 2;
        auto p_bottom = pos.y + pos.h;

        
        entity.fall_speed += 0.25;
        if(entity.fall_speed > 1.5)
            entity.foothold = nullptr;

        float velocity = entity.mass * entity.fall_speed;
        float fall_power = velocity;

        for(auto& platform : g_data.platforms)
        {
            auto& e1 = platform.edge1;
            auto& e2 = platform.edge2;

            if(e2.x == e1.x) continue;
            if(p_middle < e1.x) continue;
            if(p_middle > e2.x) continue;

            auto platform_y = e1.y + (e2.y - e1.y) * 
                (p_middle - e1.x) / (e2.x - e1.x);
            auto distance = platform_y - p_bottom;

            if(distance < 0) continue;

            if(distance < velocity + entity.speed)
            {
                velocity = distance;
                entity.fall_speed = 0;
                entity.foothold = &platform;
            }
        }

        fall_power -= velocity;
        entity.position.y += velocity;

        if(entity.foothold && entity.foothold->rotating)
        {
            SDL_FPoint impact_point {p_middle, p_bottom};
            apply_impact(*entity.foothold,
                         impact_point,
                         fall_power);
        }
    }
}

void apply_impact(Platform& platform,
                  SDL_FPoint const& point,
                  float power)
{
    auto& e1 = platform.edge1;
    auto& e2 = platform.edge2;
    SDL_FPoint pivot {
        (e1.x + e2.x) / 2,
        (e1.y + e2.y) / 2
    };

    auto p_dx = e1.x - e2.x;
    auto p_dy = e1.y - e2.y;
    auto length_sqrd = p_dx * p_dx + p_dy * p_dy;
    
    auto d_dx = pivot.x - point.x;
    auto d_dy = pivot.y - point.y;
    auto distance_sqrd = d_dx * d_dx + d_dy * d_dy;

    auto rotation = 2 * power *
                     sqrt(distance_sqrd / length_sqrd);
    if(point.x < pivot.x)
        rotation *= -1;

    // TODO rotating/falling platforms
}

