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
        angleSpeed = 0.f;
    }

    if (movementSpeed) {
        auto movment = mat3_cast(rotation)*vec3(0.f, movementSpeed*seconds, 0.f);
        model = translate(model, movment);
    }
}

void Figure::Move(int direction) noexcept {
    movementSpeed = 10.f*direction;
}

void Figure::Rotate(int direction) noexcept {
    angleSpeed = 30.f*direction;
}

glm::mat4 Figure::Model() noexcept {
    return model*glm::mat4_cast(rotation);
}
