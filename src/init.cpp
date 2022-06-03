#include "init.hpp"
#include "globals.hpp"
#include "version.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>

using std::string;


void init()
{
    create_window();
    create_renderer();
    init_data();
}

void deinit()
{
    if(g_window)
        SDL_DestroyWindow(g_window);
    if(g_renderer)
        SDL_DestroyRenderer(g_renderer);

    g_window = nullptr;
    g_renderer = nullptr;

    SDL_Quit();
}


void create_window()
{
    g_window = SDL_CreateWindow(
        PROJECT_NAME,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        0
    );

    if(!g_window)
    {
        string error = "Could not create window.\n";
        error += "SDL_Error: \n";
        error += SDL_GetError();
        std::runtime_error(error.c_str());
    }
}

void create_renderer()
{
    g_renderer = SDL_CreateRenderer(
        g_window,
        -1,
        SDL_RENDERER_PRESENTVSYNC
    );

    if(!g_renderer)
    {
        string error = "Could not create renderer.\n";
        error += "SDL_Error: \n";
        error += SDL_GetError();
        std::runtime_error(error.c_str());
    }
}


void init_data()
{
    Entity player;
    player.position = {40, 0, 24, 56};
    g_data.entities.emplace_back(player);

    g_data.platforms.push_back({
        { 40, 500},
        {760, 500},
        false
    });

    g_data.platforms.push_back({
        {160, 420},
        {280, 320}
    });

    g_data.platforms.push_back({
        {520, 320},
        {640, 420}
    });

    g_data.platforms.push_back({
        {400, 320},
        {520, 320},
    });
}
