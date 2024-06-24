#include "Figure.hxx"
#include "Renderer.hxx"
#include <glad/glad.h>
#include <glm/ext.hpp>

using namespace glm;

void Figure::Init() noexcept {
    static vec3 vertices[] = {
        glm::vec3(-16.f, 16.f, 0.f),
        glm::vec3(-16.f, -16.f, 0.f),
        glm::vec3(16.f, -16.f, 0.f),
        glm::vec3(16.f, 16.f, 0.f)
    };

    static uint32_t indices[] = { 0, 1, 3, 1, 2, 3 };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
            sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    rotation = quat_cast(mat4(1.f));
}

void Figure::Release() noexcept {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Figure::Update(float delta) noexcept {
    if (moveSpeed) {
        position += mat3_cast(rotation)*
                vec3(0.f, moveSpeed*delta, 0.f);
    }
    if (rotateSpeed) {
        rotation = rotate(rotation,
                rotateSpeed*delta, { 0.f, 0.f, 1.f });
    }
}

void Figure::Move(float factor) noexcept {
    moveSpeed = maxMoveSpeed*factor;
}

void Figure::Rotate(float factor) noexcept {
    rotateSpeed = maxRotateSpeed*factor;
}

glm::mat4 Figure::Model() noexcept {
    return translate(mat4(1.f), position)*mat4_cast(rotation);
}
