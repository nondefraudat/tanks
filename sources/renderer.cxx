#include "Renderer.hxx"

#include "World.hxx"
#include "Figure.hxx"
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/ext.hpp>
#include <cassert>

using namespace glm;

Renderer::Renderer() noexcept {
    InitSDL();
    InitOpenGL();
}

Renderer::~Renderer() noexcept {
    program.Release();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::Target(World *world) noexcept {
    this->world = world;
}

void Renderer::Render(float delta) noexcept {
    deltaCache += delta;
    if (deltaCache < 1.f/12.f) {
        return;
    }
    deltaCache -= 1.f/12.f;

    glClearColor(.5f, .5f, .5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    program.UpdateView(world->GetCamera().Model());
    for (Figure &figure : world->Figures()) {
        program.Exec(figure.vao, figure.Model());
    }
    
    SDL_GL_SwapWindow(window);
}

void Renderer::InitSDL() noexcept {
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    window = SDL_CreateWindow("Tanks",
            640, 480, SDL_WINDOW_OPENGL);
    assert(window != nullptr);
    glContext = SDL_GL_CreateContext(window);
}

void Renderer::InitOpenGL() noexcept {
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));
    program.Load();
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    program.UpdateProjection(static_cast<float>(windowWidth),
            static_cast<float>(windowHeight));
}
