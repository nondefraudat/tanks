#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct SDL_Window;
struct SDL_GLContextState;

class renderer {
protected:
    renderer() noexcept;
    ~renderer() noexcept;

public:
    void clear() noexcept;
    void move_test_figure(glm::vec3 movement) noexcept;
    void rotate_test_figure(float angle) noexcept;
    void render_test_figure() noexcept;
    void update() noexcept;

private:
    SDL_Window *window;
    SDL_GLContextState *gl_context;

    uint32_t shader_program;
    uint32_t vbo, vao, ebo;

    glm::mat4 model, view, projection;
    uint32_t model_id, view_id, projection_id;
    glm::quat rotation;
    
    void init_sdl() noexcept;
    void init_gl() noexcept;
    void init_test_figure() noexcept;
};
