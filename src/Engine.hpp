#ifndef INCLUDE_ENGINE_HPP
#define INCLUDE_ENGINE_HPP

struct SDL_Window;
struct SDL_Renderer;
struct Data;
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

    void poll_events();
    void render();

    void jump(Entity*);
    void drop_down(Entity*);

};

#endif // INCLUDE_ENGINE_HPP
