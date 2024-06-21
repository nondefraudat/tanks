#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>
#include <cstdint>

class Renderer;

class Figure {
public:
    uint32_t vao, vbo, ebo;

    void Init(Renderer *renderer) noexcept;
    void Release() noexcept;
    void Update(uint64_t deltaTime) noexcept;

    void Move(int direction) noexcept;
    void Rotate(int direction) noexcept;

    glm::mat4 Model() noexcept;

private:
    Renderer *renderer = nullptr;

    float movementSpeed = 0.f;
    float angleSpeed = 0.f;

    glm::mat4 model = { 1.f };
    glm::quat rotation;
};
