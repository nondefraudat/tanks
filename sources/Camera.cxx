#include "Camera.hxx"
#include "Figure.hxx"
#include <glm/ext.hpp>

void Camera::Chase(Figure *figure) noexcept {
    this->figure = figure;
}

void Camera::Update(uint64_t deltaTime) noexcept {
    // TODO
}

glm::mat4 Camera::Model() noexcept {
    return translate(figure->Model(), {0.f, 0.f, -1.f});
}
