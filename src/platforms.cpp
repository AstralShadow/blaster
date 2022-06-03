#include "globals.hpp"
#include "core.hpp"
#include <cmath>


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
