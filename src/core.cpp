#include "globals.hpp"
#include "core.hpp"
#include <SDL2/SDL_events.h>


void run()
{
    g_running = true;
    
    while(g_running)
    {
        tick();
        poll_events();
        render();
    }
}


void poll_events()
{
    SDL_Event ev;
    while(SDL_PollEvent(&ev))
    {
        switch(ev.type)
        {
            case SDL_QUIT:
                g_running = false;
                break;
        }
    }
}
