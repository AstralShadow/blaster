#ifndef INCLUDE_ENGINE_HPP
#define INCLUDE_ENGINE_HPP

struct SDL_Window;
struct SDL_Renderer;


class Engine
{
public:
    Engine();
    ~Engine();

    void run();

private:
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    bool _running = false;
    

    void create_window();
    void create_renderer();

    void tick();
    void poll_events();
    void render();

};

#endif // INCLUDE_ENGINE_HPP
