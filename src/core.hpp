#ifndef INCLUDE_CORE_HPP
#define INCLUDE_CORE_HPP

#include "data.hpp"

void run();

void tick();
void move_player();
void poll_events();
void render();

void apply_gravity();
void apply_impact(Platform&,
                  SDL_FPoint const& point,
                  float power);

void jump(Entity&);
void drop_down(Entity&);
void move(Entity&, SDL_FPoint const& direction);

void generate_loot();
void collect_loot();

#endif // INCLUDE_CORE_HPP
