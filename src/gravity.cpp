#include "globals.hpp"
#include "core.hpp"
#include "geometry.hpp"
#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>


void apply_gravity()
{
    for(auto& entity : g_data.entities)
    {
        auto const& pos = entity.position;
        auto p_middle = pos.x + pos.w / 2;
        auto p_bottom = pos.y + pos.h;

        SDL_FPoint velocity {
            entity.velocity.x,
            entity.velocity.y * entity.mass
        };

        SDL_FPoint old_position {
            entity.position.x - velocity.x + entity.position.w / 2,
            entity.position.y + entity.position.h
        };
        SDL_FPoint new_position {
            entity.position.x + entity.position.w / 2,
            entity.position.y + velocity.y + entity.position.h
        };

        
        if(entity.velocity.y > 0)
        for(auto& platform : g_data.platforms)
        {
            auto& e1 = platform.edge1;
            auto& e2 = platform.edge2;

            if(e2.x == e1.x) continue;
            if(p_middle < e1.x) continue;
            if(p_middle > e2.x) continue;
            
            bool in_range = segment_intersection(
                old_position, new_position,
                platform.edge1, platform.edge2,
                &new_position
            );

            if(in_range)
            {
                entity.velocity.y = 0;
                entity.foothold = &platform;
            }
        }

        float fall_power = std::hypot(velocity.x, velocity.y)
                         - std::hypot(new_position.x - old_position.x,
                                      new_position.y - old_position.y);

        entity.position.x = new_position.x - entity.position.w / 2;
        entity.position.y = new_position.y - entity.position.h;

        if(!entity.foothold)
            entity.velocity.y += g_gravity;
        
        
        if(entity.foothold && entity.foothold->rotating)
        {
            SDL_FPoint impact_point {p_middle, p_bottom};
            apply_impact(*entity.foothold,
                         impact_point,
                         fall_power);
        }
    }
}

