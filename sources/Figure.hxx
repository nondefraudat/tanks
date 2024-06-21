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

    void PushingForce(float power) noexcept;
    void RotatingForce(float angleSpeed) noexcept;

    glm::mat4 Model() noexcept;

private:
    Renderer *renderer = nullptr;

    float maxSpeed = 10.f;
    float minSpeed = -5.f;
    float speed = 0.f;
    float pushingForce = 0.f;
    float angleSpeed = 0.f;

    glm::mat4 model = { 1.f };
    glm::quat rotation;
};
