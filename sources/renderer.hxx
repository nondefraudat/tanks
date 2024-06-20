#pragma once

#include "shader_program.hxx"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <cstdint>

struct SDL_Window;
struct SDL_GLContextState;

class renderer : shader_program {
protected:
    renderer() noexcept;
    ~renderer() noexcept;

public:
    void clear() noexcept;
    void move_test_figure(glm::vec3 movement) noexcept;
    void rotate_test_figure(float angle) noexcept;
    void render_test_figure() noexcept;
    // void render_figure() noexcept;
    void update() noexcept;

private:
    SDL_Window *window;
    SDL_GLContextState *gl_context;

    int window_width, window_height;

    uint32_t shader_program;
    uint32_t vbo, vao, ebo;

    glm::quat rotation;
    
    void init_sdl() noexcept;
    void init_gl() noexcept;
    void init_test_figure() noexcept;
};
