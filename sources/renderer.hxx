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
    void Render(uint64_t deltaTime) noexcept;

    void EnableFigure(Figure *figure) noexcept;
    void DisableFigure(Figure *figure) noexcept;

private:
    World *world;

    SDL_Window *window;
    SDL_GLContextState *glContext;

    Program program;

    uint64_t deltaCache = 0;

    void InitSDL() noexcept;
    void InitOpenGL() noexcept;
};
