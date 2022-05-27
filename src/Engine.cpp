#include "Engine.hpp"
#include "Data.hpp"
#include "version.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>
#include <iostream>

using std::string;
using std::endl;
using std::cout;


Engine::Engine()
{
    cout << "Initializing..." << endl;
    this->create_window();
    this->create_renderer();
    this->init_data();
}

Engine::~Engine()
{
    if(_window)
        SDL_DestroyWindow(_window);
    if(_renderer)
        SDL_DestroyRenderer(_renderer);
    if(_data)
        delete _data;

    _window = nullptr;
    _renderer = nullptr;
    _data = nullptr;
}


void Engine::create_window()
{
    _window = SDL_CreateWindow(
        PROJECT_NAME,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        0
    );

    if(!_window)
    {
        string error = "Could not create window.\n";
        error += "SDL_Error: \n";
        error += SDL_GetError();
        std::runtime_error(error.c_str());
    }
}

void Engine::create_renderer()
{
    _renderer = SDL_CreateRenderer(
        _window,
        -1,
        SDL_RENDERER_PRESENTVSYNC
    );

    if(!_renderer)
    {
        string error = "Could not create renderer.\n";
        error += "SDL_Error: \n";
        error += SDL_GetError();
        std::runtime_error(error.c_str());
    }
}

void Engine::init_data()
{
    _data = new Data;

    Entity player;
    player.position = {40, 0, 24, 56};
    _data->entities.emplace_back(player);

    _data->platforms.push_back({
        { 40, 500},
        {760, 500}
    });

    _data->platforms.push_back({
        {160, 420},
        {280, 420}
    });

    _data->platforms.push_back({
        {520, 420},
        {640, 420}
    });
}


void Engine::run()
{
    cout << "Running "
         << PROJECT_NAME << ' '
         << VERSION_MAJOR << '.'
         << VERSION_MINOR << endl;
    _running = true;

    while(_running)
    {
        this->tick();
        this->poll_events();
        this->render();
    }

    cout << endl << "Closing "
         << PROJECT_NAME << ' '
         << VERSION_MAJOR << '.'
         << VERSION_MINOR << endl;
}
