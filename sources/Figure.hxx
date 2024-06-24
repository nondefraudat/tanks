#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>
#include <cstdint>

class Renderer;

class Figure {
public:
    uint32_t vao, vbo, ebo;
    float maxMoveSpeed = 20.f, maxRotateSpeed = glm::radians(45.f);

    glm::vec3 position;
    glm::quat rotation;

    void Init() noexcept;
    void Release() noexcept;
    void Update(float delta) noexcept;

    void Move(float factor) noexcept;
    void Rotate(float factor) noexcept;

    glm::mat4 Model() noexcept;

private:
    Renderer *renderer = nullptr;

    float moveSpeed = 0.f; // pxl/sec
    float rotateSpeed = 0.f; // rad/sec
};
