#include "Program.hxx"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>

using namespace std;
using namespace glm;

void Program::Load() noexcept {
    programLocation = glCreateProgram();
    LoadShader("../shaders/main.fsh", GL_FRAGMENT_SHADER);
    LoadShader("../shaders/main.vsh", GL_VERTEX_SHADER);
    glLinkProgram(programLocation);
    glUseProgram(programLocation);
    InitLocatins();
}

void Program::UpdateProjection(float width, float height) noexcept {
    mat4 projection = perspective(radians(90.f), width/height, .1f, 2.f);
    mat4 scale = glm::scale(mat4(1.f), vec3(2.f/height));
    glUniformMatrix4fv(scaleLocation, 1, GL_FALSE, value_ptr(scale));
    glUniformMatrix4fv(projectinLocation, 1, GL_FALSE, value_ptr(projection));
}

void Program::UpdateView(const glm::mat4 &view) noexcept {
    glUniformMatrix4fv(viewLocaton, 1, GL_FALSE, value_ptr(view));
}

void Program::Exec(uint32_t vao, const glm::mat4 &model) noexcept {
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Program::LoadShader(const char *shaderPath, uint32_t shaderType) noexcept {
    ifstream file = std::ifstream(shaderPath);
    
    file.seekg(0, std::ios::end);
    std::string fileData(static_cast<size_t>(file.tellg()), '\0');
    file.seekg(0, std::ios::beg);
    
    fileData.assign((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
    
    uint32_t shaderLocation = glCreateShader(shaderType);
    const char *shaderSource[] = { fileData.data() };
    glShaderSource(shaderLocation, 1, shaderSource, nullptr);
    glCompileShader(shaderLocation);
    glAttachShader(programLocation, shaderLocation);
    glDeleteShader(shaderLocation);
}

void Program::InitLocatins() noexcept {
    modelLocation = glGetUniformLocation(programLocation, "model");
    scaleLocation = glGetUniformLocation(programLocation, "scale");
    viewLocaton = glGetUniformLocation(programLocation, "view");
    projectinLocation = glGetUniformLocation(programLocation, "projection");
}

void Program::Release() noexcept {
    glDeleteProgram(programLocation);
}
