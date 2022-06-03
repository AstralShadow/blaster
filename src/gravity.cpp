#include "globals.hpp"
#include "core.hpp"


void apply_gravity()
{
    for(auto& entity : g_data.entities)
    {
        auto const& pos = entity.position;
        auto p_middle = pos.x + pos.w / 2;
        auto p_bottom = pos.y + pos.h;

        
        entity.velocity.y += g_gravity;
        if(entity.velocity.y > 1.5)
            entity.foothold = nullptr;

        float velocity = entity.mass * entity.velocity.y;
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

            if(distance < velocity + entity.max_speed)
            {
                velocity = distance;
                entity.velocity.y = 0;
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

