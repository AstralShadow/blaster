#include "Engine.hpp"
#include "Data.hpp"
#include <SDL2/SDL_keyboard.h>
#include <cmath>
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

    this->move(player, &motion);
}

void Engine::apply_gravity()
{
    for(auto& entity : _data->entities)
    {
        auto const& pos = entity.position;
        auto p_middle = pos.x + pos.w / 2;
        auto p_bottom = pos.y + pos.h;

        
        entity.fall_speed += 0.25;
        if(entity.fall_speed > 1.5)
            entity.support = nullptr;

        float velocity = entity.mass * entity.fall_speed;
        float fall_power = velocity;

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

            if(distance < 0) continue;

            if(distance < velocity + entity.speed)
            {
                velocity = distance;
                entity.fall_speed = 0;
                entity.support = &platform;
            }
        }

        fall_power -= velocity;
        entity.position.y += velocity;

        if(entity.support && !entity.support->solid)
        {
            SDL_FPoint impact_point {p_middle, p_bottom};
            this->apply_impact(entity.support,
                               &impact_point,
                               fall_power);
        }
    }
}

void Engine::apply_impact(Platform* platform,
                          SDL_FPoint* point,
                          float power)
{
    auto& e1 = platform->edge1;
    auto& e2 = platform->edge2;
    SDL_FPoint p_mid {
        (e1.x + e2.x) / 2,
        (e1.y + e2.y) / 2
    };

    auto p_dx = e1.x - e2.x;
    auto p_dy = e1.y - e2.y;
    auto length_sqrd = p_dx * p_dx + p_dy * p_dy;
    
    auto d_dx = p_mid.x - point->x;
    auto d_dy = p_mid.y - point->y;
    auto distance_sqrd = d_dx * d_dx + d_dy * d_dy;

    auto rotation = 2 * power *
                     sqrt(distance_sqrd / length_sqrd);
    if(point->x < p_mid.x)
        rotation *= -1;

    // TODO rotating/falling platforms
}


void Engine::jump(Entity* entity)
{
    if(entity->support)
        entity->fall_speed = -entity->mass
                              * entity->jump_factor;
    entity->support = nullptr;
}

void Engine::drop_down(Entity* entity)
{
    if(entity->support && !entity->support->solid)
    {
        entity->position.y += 1;
        entity->support = nullptr;
    }
}

void Engine::move(Entity* entity, SDL_FPoint* motion)
{
    if(motion->y < 0) this->jump(entity);
    if(motion->y > 0) this->drop_down(entity);
    if(motion->x == 0) return;

    auto const motion_x = motion->x * entity->speed;

    if(!entity->support)
    {
        entity->position.x += motion_x;
    }
    else
    {
        auto& platform = *(entity->support);
        auto dx = platform.edge1.x - platform.edge2.x;
        auto dy = platform.edge1.y - platform.edge2.y;
        auto angle = atan2(dy, dx);
        
        entity->position.y -= sin(angle) * motion_x + .1;
        entity->position.x -= cos(angle) * motion_x;

        if(entity->position.x > platform.edge2.x)
            entity->position.y -= 1;
        if(entity->position.x < platform.edge1.x)
            entity->position.y -= 1;
    }
}
