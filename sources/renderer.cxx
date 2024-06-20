#include "renderer.hxx"

#include "logger.hxx"

#include <glm/ext.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <cassert>

renderer::renderer() noexcept {
    init_sdl();
    init_gl();
    init_test_figure();
}

renderer::~renderer() noexcept {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glDeleteProgram(shader_program);

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderer::clear() noexcept {
    glClearColor(.5f, .5f, .5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderer::move_test_figure(glm::vec3 movement) noexcept {
    auto translated = glm::mat3_cast(rotation)*movement;
    model = glm::translate(model, translated);
}

void renderer::rotate_test_figure(float angle) noexcept {
    rotation = glm::rotate(rotation, angle, { 0.f, 0.f, 1.f });
}


void renderer::render_test_figure() noexcept {
    temp_model = model*glm::mat4_cast(rotation);
    shader_program::bind();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void renderer::update() noexcept {
    SDL_GL_SwapWindow(window);
}

void renderer::init_sdl() noexcept {
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    window = SDL_CreateWindow("Tanks",
            640, 480, SDL_WINDOW_OPENGL);
    assert(window != nullptr);
    gl_context = SDL_GL_CreateContext(window);
    SDL_GetWindowSize(window, &window_width, &window_height);
}

void renderer::init_gl() noexcept {
    gladLoadGLLoader(
            reinterpret_cast<GLADloadproc>
            (SDL_GL_GetProcAddress));
            
    glViewport(0, 0, window_width, window_height);

    shader_program::init();
}

void renderer::init_test_figure() noexcept {
    glm::vec3 vertices[] = {
        glm::vec3(-16.f, 16.f, 0.f),
        glm::vec3(-16.f, -16.f, 0.f),
        glm::vec3(16.f, -16.f, 0.f),
        glm::vec3(16.f, 16.f, 0.f)
    };
    
    static uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
            vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
            3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    
    glBindVertexArray(0);

    rotation = glm::quat_cast(glm::mat4(1.f));
    auto factor = 2.f/window_height;
    model = glm::scale(model, glm::vec3(factor));

    view = glm::translate(glm::mat4(1.f), { 0.f, 0.f, -1.f });

    auto aspect = float(window_width)/window_height;
    projection = glm::perspective(glm::radians(90.f), aspect, .1f, 2.f);
}
