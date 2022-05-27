#include "globals.hpp"
#include "core.hpp"
#include <SDL2/SDL_keyboard.h>


void move_player()
{
    static auto kb_state = SDL_GetKeyboardState(nullptr);

    uint8_t const key_up[] = {
        SDL_SCANCODE_W,
        SDL_SCANCODE_UP
    };
    uint8_t const key_down[] = {
        SDL_SCANCODE_S,
        SDL_SCANCODE_DOWN
    };
    uint8_t const key_left[] = {
        SDL_SCANCODE_A,
        SDL_SCANCODE_LEFT
    };
    uint8_t const key_right[] = {
        SDL_SCANCODE_D,
        SDL_SCANCODE_RIGHT
    };

    Entity* player = &g_data.entities[0];
    SDL_FPoint motion = {0, 0};

    for(auto up : key_up)
        if(kb_state[up])
            motion.y--;

    for(auto down : key_down)
        if(kb_state[down])
            motion.y++;

    for(auto left : key_left)
        if(kb_state[left])
            motion.x--;

    for(auto right : key_right)
        if(kb_state[right])
            motion.x++;

    move(player, &motion);
}
