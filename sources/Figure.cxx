#include "Figure.hxx"
#include "Renderer.hxx"
#include <glm/ext.hpp>

using namespace glm;

void Figure::Init(Renderer *renderer) noexcept {
    renderer->EnableFigure(this);
    rotation = quat_cast(mat4(1.f));
}

void Figure::Release() noexcept {
    if (renderer) {
        renderer->DisableFigure(this);
    }
}

void Figure::Update(uint64_t deltaTime) noexcept {
    auto seconds = float(deltaTime)/1000.f;

    if (angleSpeed) {
        rotation = rotate(rotation,
                angleSpeed*seconds, { 0.f, 0.f, 1.f });
    }
    angleSpeed = 0.f;

    speed += pushingForce*seconds;
    if (speed > maxSpeed) {
        speed = maxSpeed;
    }
    else if (speed < minSpeed) {
        speed = minSpeed;
    }
    if (speed) {
        auto movment = mat3_cast(rotation)*vec3(0.f, speed, 0.f);
        model = translate(model, movment);
        pushingForce = speed = 0;
    }
}

void Figure::PushingForce(float power) noexcept {
    pushingForce = power;
}

void Figure::RotatingForce(float angleSpeed) noexcept {
    this->angleSpeed = angleSpeed;
}

glm::mat4 Figure::Model() noexcept {
    return model*glm::mat4_cast(rotation);
}
