#include "Engine.hpp"
#include "Data.hpp"
#include <SDL2/SDL_render.h>


void Engine::render()
{
    auto& _rnd = _renderer;

    SDL_SetRenderDrawColor(_rnd, 0, 0, 0, 255);
    SDL_RenderClear(_rnd);

    SDL_SetRenderDrawColor(_rnd, 255, 0, 0, 255);
    for(auto const& entity : _data->entities)
    {
        SDL_RenderDrawRectF(_rnd, &entity.position);
    }

    SDL_SetRenderDrawColor(_rnd, 0, 255, 0, 255);
    for(auto const& platform : _data->platforms)
    {
        SDL_RenderDrawLineF(_rnd, platform.edge1.x,
                                  platform.edge1.y,
                                  platform.edge2.x,
                                  platform.edge2.y);
    }

    SDL_RenderPresent(_rnd);
}
