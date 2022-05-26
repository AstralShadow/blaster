#include "Engine.hpp"
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
    cout << "Initializing." << endl;
    this->create_window();
    this->create_renderer();
}

Engine::~Engine()
{
    if(_window)
        SDL_DestroyWindow(_window);
    if(_renderer)
        SDL_DestroyRenderer(_renderer);

    _window = nullptr;
    _renderer = nullptr;
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

}

void Engine::tick()
{
    
}

void Engine::poll_events()
{
    SDL_Event ev;
    while(SDL_PollEvent(&ev))
    {
        switch(ev.type)
        {
            case SDL_QUIT:
                _running = false;
                break;
        }
    }
}

void Engine::render()
{
    auto& _rnd = _renderer;

    SDL_SetRenderDrawColor(_rnd, 0, 0, 0, 255);
    SDL_RenderClear(_rnd);


    SDL_RenderPresent(_rnd);
}
