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

void Renderer::Render(uint64_t deltaTime) noexcept {
    deltaCache += deltaTime;
    if (deltaCache < 1000/12) {
        return;
    }
    deltaCache -= 1000/12;

    glClearColor(.5f, .5f, .5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    program.UpdateView(world->GetCamera().Model());
    for (Figure &figure : world->Figures()) {
        program.Exec(figure.vao, figure.Model());
    }
    
    SDL_GL_SwapWindow(window);
}

void Renderer::EnableFigure(Figure *figure) noexcept {
    static vec3 vertices[] = {
        glm::vec3(-16.f, 16.f, 0.f),
        glm::vec3(-16.f, -16.f, 0.f),
        glm::vec3(16.f, -16.f, 0.f),
        glm::vec3(16.f, 16.f, 0.f)
    };

    static uint32_t indices[] = { 0, 1, 3, 1, 2, 3 };

    glGenVertexArrays(1, &figure->vao);
    glBindVertexArray(figure->vao);
    
    glGenBuffers(1, &figure->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, figure->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &figure->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, figure->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

void Renderer::DisableFigure(Figure *figure) noexcept {
    glDeleteVertexArrays(1, &figure->vao);
    glDeleteBuffers(1, &figure->vbo);
    glDeleteBuffers(1, &figure->ebo);
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
