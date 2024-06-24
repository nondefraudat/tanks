#include "Camera.hxx"
#include "Figure.hxx"
#include <glm/ext.hpp>

using namespace glm;

void Camera::Chase(Figure *figure) noexcept {
    this->figure = figure;
}

void Camera::Update(float delta) noexcept {
    // TODO
}

glm::mat4 Camera::Model() noexcept {
    static auto foo = translate(mat4(1.f), { 0.f, 0.f, -1.f });
    return foo;
}
