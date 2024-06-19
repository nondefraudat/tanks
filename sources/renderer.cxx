#include "renderer.hxx"

#include <glm/ext.hpp>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <cassert>

static const auto vertex_shader_source = 
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"uniform mat4 model;\n"
"void main() {\n"
"   gl_Position = model*vec4(pos.x, pos.y, pos.z, 1.0);\n"
"}\n";

static const auto fragment_shader_source =
"#version 330 core\n"
"out vec4 frag_color;\n"
"void main() {\n"
"   frag_color = vec4(1.f, 1.f, 1.f, 1.f);\n"
"}\n";

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

void renderer::render_test_figure() noexcept {
    glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void renderer::update() noexcept {
    SDL_GL_SwapWindow(window);
}

void renderer::init_sdl() noexcept {
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    window = SDL_CreateWindow("test",
            400, 400, SDL_WINDOW_OPENGL);
    assert(window != nullptr);
    gl_context = SDL_GL_CreateContext(window);
}

void renderer::init_gl() noexcept {
    gladLoadGLLoader(
            reinterpret_cast<GLADloadproc>
            (SDL_GL_GetProcAddress));

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1,
            &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1,
            &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glUseProgram(shader_program);
    
    model_id = glGetUniformLocation(shader_program, "model");
}

void renderer::init_test_figure() noexcept {
    static float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    
    static uint32_t indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
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

    model = glm::mat4(1.f);
    model = glm::scale(model, glm::vec3(.05f));

    glm::vec3 camera(0.f, 0.f, 1.f);
    glm::vec3 world_up(0.f, 1.f, 0.f);
    glm::vec3 camera_front(0.f, 0.f, -1.f);
    
    view = glm::lookAt(camera, camera + camera_front, world_up);

    float fov = 90.f;
    float nearPlane = .1f;
    float farPlane = 5000.f;
    projection = glm::perspective(glm::radians(fov),
            1.f, nearPlane, farPlane);
}

void renderer::move_test_figure(glm::vec3 movement) noexcept {
    model = glm::translate(model, movement);
}
