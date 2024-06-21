#include "World.hxx"

#include <glm/ext.hpp>

using namespace glm;
using namespace std;

void World::PlaceCamera(Camera &&camera) noexcept {
    this->camera = camera;
}

Figure *World::Place(Figure &&figure) noexcept {
    figures.emplace_back(figure);
    return &figures.back();
}

void World::Update(uint64_t deltaTime) noexcept {
    for (Figure &figure : figures) {
        figure.Update(deltaTime);
    }
    camera.Update(deltaTime);
}

void World::Release() noexcept {
    figures.clear();
}

Camera &World::GetCamera() noexcept {
    return camera;
}

std::list<Figure> &World::Figures() noexcept
{
    return figures;
}
