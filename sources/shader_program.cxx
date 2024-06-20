#include "shader_program.hxx"
#include "logger.hxx"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <fstream>

void shader_program::init() noexcept {
    gl_program = glCreateProgram();
    load("../shaders/main.fsh", GL_FRAGMENT_SHADER);
    load("../shaders/main.vsh", GL_VERTEX_SHADER);
    glLinkProgram(gl_program);
    glUseProgram(gl_program);
    model_id = glGetUniformLocation(gl_program, "model");
    view_id = glGetUniformLocation(gl_program, "view");
    projection_id = glGetUniformLocation(
            gl_program, "projection");
}

void shader_program::bind() noexcept {
    glUniformMatrix4fv(model_id, 1,
            GL_FALSE, glm::value_ptr(temp_model));
    glUniformMatrix4fv(view_id, 1,
            GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projection_id, 1,
            GL_FALSE, glm::value_ptr(projection));
}

void shader_program::load(
        const char *file_path, int shader_type) noexcept {
    auto shader = glCreateShader(shader_type);
    std::string shader_source = load(file_path);
    auto shader_data = shader_source.data();
    glShaderSource(shader, 1, &shader_data, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success){
        logger::log("shader_compile_error");
    }
    glAttachShader(gl_program, shader);
    glDeleteShader(shader);
}

std::string shader_program::load(
        const char *file_path) noexcept {
    auto file = std::ifstream(file_path);
    file.seekg(0, std::ios::end);
    auto buffer = std::string(
            static_cast<size_t>(file.tellg()), '\0');
    file.seekg(0, std::ios::beg);
    buffer.assign((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
    return buffer;
}
