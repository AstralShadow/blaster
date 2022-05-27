#ifndef INCLUDE_GLOBALS_HPP
#define INCLUDE_GLOBALS_HPP

#include "Data.hpp"

struct SDL_Window;
struct SDL_Renderer;


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern Data g_data;
extern bool g_running;

#endif // INCLUDE_GLOBALS_HPP
