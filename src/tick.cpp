#include "globals.hpp"
#include "core.hpp"


void tick()
{
    move_player();
    apply_gravity();
    collect_loot();
    generate_loot();
}
