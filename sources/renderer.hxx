#pragma once

#include "Program.hxx"
#include <cstdint>

class World;
class Figure;

struct SDL_Window;
struct SDL_GLContextState;

class Renderer {
public:
    Renderer() noexcept;
    ~Renderer() noexcept;
    
    void Target(World *world) noexcept;
    void Render(float delta) noexcept;

private:
    World *world;

    SDL_Window *window;
    SDL_GLContextState *glContext;

    Program program;

    float deltaCache = 0.f;

    void InitSDL() noexcept;
    void InitOpenGL() noexcept;
};
