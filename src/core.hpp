#ifndef INCLUDE_CORE_HPP
#define INCLUDE_CORE_HPP

#include "Data.hpp"

void run();

void tick();
void move_player();
void poll_events();
void render();

void apply_gravity();
void apply_impact(Platform*, SDL_FPoint*, float power);

void jump(Entity*);
void drop_down(Entity*);
void move(Entity*, SDL_FPoint* direction);

void collect_loot();
void generate_loot();

#endif // INCLUDE_CORE_HPP
