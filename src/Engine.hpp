#ifndef INCLUDE_ENGINE_HPP
#define INCLUDE_ENGINE_HPP

struct SDL_Window;
struct SDL_Renderer;
struct SDL_FPoint;
struct Data;
struct Platform;
struct Entity;


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
    Data* _data = nullptr;
    

    void create_window();
    void create_renderer();
    void init_data();

    void tick();
    void move_player();
    void apply_gravity();
    void apply_impact(Platform*, SDL_FPoint*, float power);

    void poll_events();
    void render();

    void jump(Entity*);
    void drop_down(Entity*);
    void move(Entity*, SDL_FPoint* direction);

};

#endif // INCLUDE_ENGINE_HPP
