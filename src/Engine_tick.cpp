#include "Engine.hpp"
#include "Data.hpp"
#include <SDL2/SDL_keyboard.h>
#include <iostream>

using std::cout;
using std::endl;


void Engine::tick()
{
    this->move_player();
    this->apply_gravity();
}

void Engine::move_player()
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

    Entity* player = &_data->entities[0];

    for(auto up : key_up)
        if(kb_state[up])
            jump(player);

    for(auto down : key_down)
        if(kb_state[down])
            drop_down(player);

    for(auto left : key_left)
        if(kb_state[left])
            player->position.x -= 5;

    for(auto right : key_right)
        if(kb_state[right])
            player->position.x += 5;
}

void Engine::apply_gravity()
{
    for(auto& entity : _data->entities)
    {
        auto const& pos = entity.position;
        auto p_middle = pos.x + pos.w / 2;
        auto p_bottom = pos.y + pos.h;

        
        entity.fall_speed += 0.15;
        //if(entity.fall_speed == 0)
            //entity.fall_speed = 1;

        float fall = entity.mass * entity.fall_speed;
        for(auto& platform : _data->platforms)
        {
            auto& e1 = platform.edge1;
            auto& e2 = platform.edge2;

            if(e2.x == e1.x) continue;
            if(p_middle < e1.x) continue;
            if(p_middle > e2.x) continue;

            auto platform_y = e1.y + (e2.y - e1.y) * 
                (p_middle - e1.x) / (e2.x - e1.x);
            auto distance = platform_y - p_bottom;

            if(distance >= 0 && distance < fall)
            {
                fall = distance;
                entity.fall_speed = 0;
            }
        }

        entity.position.y += fall;
    }
}

void Engine::jump(Entity* entity)
{
    if(entity->fall_speed == 0)
        entity->fall_speed = -5;
}

void Engine::drop_down(Entity* entity)
{

}

