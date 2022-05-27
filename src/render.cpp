#include "globals.hpp"
#include "core.hpp"
#include <SDL2/SDL_render.h>


void render()
{
    auto& rnd = g_renderer;

    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    SDL_SetRenderDrawColor(rnd, 255, 0, 0, 255);
    for(auto const& entity : g_data.entities)
    {
        SDL_RenderDrawRectF(rnd, &entity.position);
    }

    SDL_SetRenderDrawColor(rnd, 0, 255, 0, 255);
    for(auto const& platform : g_data.platforms)
    {
        SDL_RenderDrawLineF(rnd, platform.edge1.x,
                                 platform.edge1.y,
                                 platform.edge2.x,
                                 platform.edge2.y);
    }

    SDL_RenderPresent(rnd);
}
