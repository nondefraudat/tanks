#pragma once

#include <glm/mat4x4.hpp>
#include <cstdint>

class Figure;

class Camera {
public:
    void Chase(Figure *figure) noexcept;
    void Update(uint64_t deltaTime) noexcept;
    glm::mat4 Model() noexcept;

private:
    Figure *figure;
};
