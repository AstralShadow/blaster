#include "globals.hpp"
#include "core.hpp"
#include "random.hpp"
#include <cmath>
#include <chrono>

using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::seconds;


void generate_loot()
{
    time_point now = steady_clock::now();
    static time_point last_run = now;
    if(now < last_run + seconds(1))
        return;
    last_run = now;

    for(auto const& platform : g_data.platforms)
    {
        if(random(0, 5 * g_data.platforms.size()))
            continue;

        auto& e1 = platform.edge1;
        auto& e2 = platform.edge2;

        float position = randomf(0.0f, 1.0f);

        SDL_Point loot;
        loot.x = e1.x + (e2.x - e1.x) * position;
        loot.y = e1.y + (e2.y - e1.y) * position;
        loot.y -= 20;

        g_data.loot.push_back(loot);
    }
}

void collect_loot()
{
    auto& loot = g_data.loot;
    auto& sprite = g_data.entities[0].position;
    int x = sprite.x + sprite.w / 2;
    int y = sprite.y + sprite.h / 2;
    int range_x = sprite.w / 2 + 5;
    int range_y = sprite.h / 2 + 5;


    auto itr = loot.begin();
    while(itr != loot.end())
    {
        auto dx = std::abs(x - itr->x);
        auto dy = std::abs(y - itr->y);

        if(dx > range_x || dy > range_y)
        {
            itr++;
            continue;
        }

        itr = loot.erase(itr);
        g_data.score++;
    }
}

